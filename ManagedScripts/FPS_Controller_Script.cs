using ScriptAPI;
using System;

public class FPS_Controller_Script : Script
{
    #region Camera Movement Variables
    [Header("Camera Movement Variables")]
    public CameraComponent playerCamera;
    public float fov = 60f;
    public bool invertCamera = false;
    public bool cameraCanMove = true;
    public float mouseSensitivity = 2f;
    public float maxLookAngle = 50f;

    // Crosshair
    public bool lockCursor = true;
    public bool crosshair = true;
    //public Image crosshairObject;
    //public Sprite crosshairImage;
    //public Color crosshairColor = Color.white;

    // Internal Variables
    private float yaw = 0.0f;
    private float pitch = 0.0f;

    #region Camera Zoom Variables
    public bool enableZoom = true;
    public bool holdToZoom = false;
    //public KeyCode zoomKey = KeyCode.Mouse1;
    public float zoomFOV = 30f;
    public float zoomStepTime = 5f;

    // Internal Variables
    private bool isZoomed = false;
    #endregion

    #endregion

    #region Movement Variables
    [Header("Movement Variables")]
    public bool playerCanMove = true;
    public float walkSpeed = 2f;
    public float maxVelocityChange = 10f;
    public bool isWalking = false;

    #region Sprint
    public bool enableSprint = true;
    public bool unlimitedSprint = false;
    //public KeyCode sprintKey = KeyCode.LeftShift;
    public float sprintSpeed = 3f;
    public float currentSprintSpeed;
    public float sprintDuration = 5f;
    public float sprintCooldown = .5f;
    public float sprintFOV = 80f;
    public float sprintFOVStepTime = 10f;

    // Sprint Bar
    public bool useSprintBar = true;
    public bool hideBarWhenFull = true;
    //public CanvasGroup sprintBarCG;
    //public Image sprintBarBG;
    //public Image sprintBar;
    public float sprintBarWidthPercent = .3f;
    public float sprintBarHeightPercent = .015f;

    // Internal Variables
    public bool isSprinting = false;
    private float sprintRemaining;
    private float sprintBarWidth;
    private float sprintBarHeight;
    private bool isSprintCooldown = false;
    private float sprintCooldownReset;
    #endregion

    #region Jump
    public bool enableJump = true;
    //public KeyCode jumpKey = KeyCode.Space;
    public float jumpPower = 5f;

    // Internal Variables
    private bool isGrounded = false;
    #endregion

    #region Crouch
    public bool enableCrouch = true;
    public bool holdToCrouch = true;
    //public KeyCode crouchKey = KeyCode.LeftControl;
    public float crouchHeight = .75f;
    public float speedReduction = .5f;

    // Internal Variables
    private bool isCrouched = false;
    private Vector3 originalScale;
    #endregion

    #region Health
    public int playerHealth = 100;
    #endregion
    #endregion

    #region Head Bob
    [Header("HeadBob")]
    public bool enableHeadBob = true;
    //public TransformComponent joint;
    public float bobSpeed = 10f;
    public Vector3 bobAmount = new Vector3(.15f, .05f, 0f);

    // Internal Variables
    private Vector3 jointOriginalPos;
    private float timer = 0;
    #endregion

    public override void Awake()
    {

    }
    public override void OnEnable()
    {

    }
    public override void Start()
    {

    }
    public override void Update()
    {

    }
    public override void LateUpdate()
    {

    }
    public override void OnDisable()
    {

    }
    public override void OnDestroy()
    {

    }
}