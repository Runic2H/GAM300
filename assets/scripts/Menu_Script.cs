using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using TMPro;

public enum MenuState { INTRO, MENU, SETTINGS, GAME }
public class Menu_Script : MonoBehaviour
{
    #region DP Intro Variables
    public Image dp_Logo;
    public GameObject dpIntro_Obj;

    //Internal Variables
    private float dpTimer = 2;
    private bool displayDPIntro;
    #endregion

    #region Main Menu Variables
    public GameObject mainMenu_Obj;
    #endregion

    #region Settings Variables
    public GameObject settings_Obj;
    #endregion

    public GameObject menuCamera;
    public Canvas uiCanvas_Obj;

    private MenuState state;

    private void Update()
    {
        if (state == MenuState.INTRO)
        {
            if (dpTimer > 0)
            {
                dpTimer -= Time.deltaTime;

                var color = dp_Logo.color;
                color.a += (Time.deltaTime / 2);
                dp_Logo.color = color;
            }
            else
            {
                var color = dp_Logo.color;
                color.a -= (Time.deltaTime / 2);
                dp_Logo.color = color;

                if (color.a <= 0)
                {
                    dpIntro_Obj.SetActive(false);
                    mainMenu_Obj.SetActive(true);
                    state = MenuState.MENU;
                }
            }
        }
    }

    #region Main Menu Bttns' Methods
    public void PlayClicked()
    {
        SceneManager.LoadScene("Test Scene");
    }

    public void SettingsClicked()
    {
        mainMenu_Obj.SetActive(false);

        settings_Obj.SetActive(true);
        state = MenuState.SETTINGS;
    }
    #endregion

    #region Setting Bttns' Methods
    public void BackClicked()
    {
        settings_Obj.SetActive(false);

        mainMenu_Obj.SetActive(true);
        state = MenuState.MENU;
    }
    #endregion
}
