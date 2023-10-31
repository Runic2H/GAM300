using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.AI;

public class Pathfinding : MonoBehaviour
{
    //dictates whether the agent waits on each node
    [SerializeField]
    bool _patrolWaiting;

    //total time AI waits at each node
    [SerializeField]
    float _totalWaitTime = 3f;

    //probability of switching directions
    [SerializeField]
    float _switchProbability = 0.2f;

    //list of all patrol nodes to visit
    [SerializeField]
    List<Waypoint> _patrolPoints;

    //variables for base behavior
    [HideInInspector] public NavMeshAgent _navMeshAgent;
    int _currentPatrolIndex;
    [SerializeField] bool _travelling;
    //public bool _waiting = false;
    bool _patrolForward;
    [SerializeField] float _waitTimer;
    public LayerMask whatIsPlayer;
    [SerializeField] float attackCooldown;
    [SerializeField] float attackRange;
    bool alreadyAttacked = false;
    public float pathUpdateDelay = 0.2f;
    public FieldOfView fovCheck;

    //variabels for detection of player
    public GameObject player;
    public float sightRange;
    public bool _detected;
    public bool _seen;
    public bool _hidden;
    [SerializeField] Vector3 playerLastPosition;
    public bool _canMove;
    public bool playerInAttackRange;
    public FPS_Controller_Script playerScript;

    // Start is called before the first frame update
    void Start()
    {
        _navMeshAgent = this.GetComponent<NavMeshAgent>();

        if (_navMeshAgent == null)
        {
            Debug.LogError("Nav Mesh Agent Component Is Not Attached To " + gameObject.name);
        }
        else
        {
            if (_patrolPoints != null && _patrolPoints.Count >= 2)
            {
                _currentPatrolIndex = 0;
                SetDestination();
            }
            else
            {
                Debug.Log("Insufficient Patrol Points For Basic Patrolling Behavior");
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        playerInAttackRange = Physics.CheckSphere(transform.position, attackRange, whatIsPlayer);
        _seen = fovCheck.canSeePlayer;
        if (_seen)
        {
            Debug.Log("player spotted");
        }
        if (_canMove)
        {
            if (_travelling && !_detected)
            {
                Patrolling();
                GetComponent<AudioSource>().enabled = false;
            }
            else if (_detected && !playerInAttackRange && _seen)
            {
                Debug.Log("chasing");
                Chasing();
            }
            else if (_detected && playerInAttackRange && _seen)
            {
                Debug.Log("attacking");
                Attacking();
            }
            else if(!_detected && playerInAttackRange && !_seen)
            {
                Debug.Log("listening");
                Listening();
            }
            else if (!_detected)
            {
                //GetComponent<AudioSource>().enabled = false;
                _navMeshAgent.SetDestination(playerLastPosition);

                if ((float)System.Math.Round(transform.position.x, 2) == (float)System.Math.Round(playerLastPosition.x, 2))
                {
                    _waitTimer += Time.deltaTime;
                    Debug.LogError("waiting");

                    if (_waitTimer >= _totalWaitTime)
                    {
                        //_waiting = false;
                        _waitTimer = 0;
                        _travelling = true;
                    }
                }
            }
        }
    }

    void Patrolling()
    {
        Debug.Log("switch to patrol");
        #region check if we are close to destination
        _canMove = true;
        if (_travelling && _navMeshAgent.remainingDistance <= 1.0f)
        {
            _travelling = false;

            //if we are going to wait, then wait
            if (_patrolWaiting)
            {
                //_waiting = true;
                _waitTimer = 0f;
            }
            else
            {
                ChangePatrolPoint();
                SetDestination();
            }
        }
        #endregion

        #region Instead if we are waiting
        //if (_waiting)
        //{
        //    _waitTimer += Time.deltaTime;

        //    if (_waitTimer >= _totalWaitTime)
        //    {
        //        _waiting = false;

        //        ChangePatrolPoint();
        //        SetDestination();
        //    }
        //}
        #endregion
    }

    void Chasing()
    {
        GetComponent<AudioSource>().enabled = true;
        _navMeshAgent.SetDestination(player.transform.position);
        playerLastPosition = player.transform.position;
        //if (playerInAttackRange)
        //{
        //    Attacking();
        //}
        _travelling = false;
    }

    void Attacking()
    {
        Debug.Log("entering attack mode");
        _canMove = false;
        transform.LookAt(player.transform);
        if (!alreadyAttacked)
        {
            playerScript.playerHealth = -20;
            Debug.Log("player damaged:" + playerScript.playerHealth);
            alreadyAttacked = true;
            Invoke(nameof(ResetAttack), attackCooldown);
        }
    }

    private void ResetAttack()
    {
        Debug.Log("resetting");
        alreadyAttacked = false;
        _canMove = true;
    }

    void Listening()
    {
        Debug.Log("entering listening mode");
        _canMove = false;
        Invoke(nameof(Patrolling), 3);
    }

    private void SetDestination()
    {
        if (_patrolPoints != null)
        {
            Vector3 targetVector = _patrolPoints[_currentPatrolIndex].transform.position;
            _navMeshAgent.SetDestination(targetVector);
            _travelling = true;
            _navMeshAgent.speed = Random.Range(1, 3);
        }
    }

    //selects a new patrol point in avail list but
    //also with a small probability allows it to move forward/backwards

    private void ChangePatrolPoint()
    {
        if (Random.Range(0f, 1f) <= _switchProbability)
        {
            _patrolForward = !_patrolForward;
        }

        if (_patrolForward)
        {
            _currentPatrolIndex = (_currentPatrolIndex + 1) % _patrolPoints.Count;
        }
        else
        {
            if (--_currentPatrolIndex < 0)
            {
                _currentPatrolIndex = _patrolPoints.Count - 1;
            }
        }
    }

    private void OnCollisionEnter(Collision collision)
    {
        if (collision.gameObject.tag == "Door")
        {
            _travelling = false;

            if (collision.gameObject.GetComponent<Door_Script>().locked == true)
            {
                ChangePatrolPoint();
                SetDestination();
                Debug.Log("Changed");
            }
            else
            {
                collision.gameObject.GetComponent<Door_Script>().Open_CloseFunction();
                Debug.Log("Opened Door");
            }
        } 
        else if (collision.gameObject.tag == "MainCamera")
        {
            _canMove = false;
        } 
    }

    private void OnTriggerEnter(Collider other)
    {
        if (other.gameObject.name == "Event3_Waypoint")
        {
            _canMove = false;
        }
    }
}
