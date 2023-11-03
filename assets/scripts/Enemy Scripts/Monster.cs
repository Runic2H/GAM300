using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Monster : MonoBehaviour
{

    public Transform player;

    private Pathfinding reference;

    private float pathUpdateDeadline;
    private float attackDistance;

    private void Awake()
    {
        reference = GetComponent<Pathfinding>();
    }


    // Start is called before the first frame update
    void Start()
    {
        attackDistance = reference._navMeshAgent.stoppingDistance;
    }

    // Update is called once per frame
    void Update()
    {
        if (player != null)
        {
            bool inRange = Vector3.Distance(transform.position, player.position) <= attackDistance;

            if (inRange)
            {
                LookAtTarget();
            }
            else
            {
                UpdatePath();
            }
        }
    }

    void LookAtTarget()
    {
        Vector3 lookPos = player.position - transform.position;
        lookPos.y = 0;
        Quaternion rotation = Quaternion.LookRotation(lookPos);
        transform.rotation = Quaternion.Slerp(transform.rotation, rotation, 0.2f);
    }
    void UpdatePath()
    {
        if (Time.time >= pathUpdateDeadline)
        {
            Debug.Log("Updating Path");
            pathUpdateDeadline = Time.time + reference.pathUpdateDelay;
            reference._navMeshAgent.SetDestination(player.position);
        }
    }
}
