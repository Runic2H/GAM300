using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using UnityEngine.Rendering;
using UnityEngine.Rendering.PostProcessing;

public class Colorblind_Fliters_Script : MonoBehaviour
{
    public TextAsset FilterData;
    public GameObject myFilters;
    public TMP_Text myFilterBttnTxt;
    public Button leftBttn;
    public Button rightBttn;
    public int clickCount;
    public bool leftClicked, rightClicked;

    //Internal Variables
    private PostProcessVolume myVolume;
    private ColorGrading myCG;

    #region Set CB Filter Values From Json
    [System.Serializable]

    public class Filter
    {
        public string ID;
        public string Name;
        public float Red_R;
        public float Red_G;
        public float Red_B;
        public float Green_R;
        public float Green_G;
        public float Green_B;
        public float Blue_R;
        public float Blue_G;
        public float Blue_B;
    }

    [System.Serializable]

    public class FilterList
    {
        public Filter[] filter;
    }

    public FilterList myFilterList = new FilterList();

    //Individual 'Color Grading' RGB values
    private float CG_Red_R;
    private float CG_Red_G;
    private float CG_Red_B;
    private float CG_Green_R;
    private float CG_Green_G;
    private float CG_Green_B;
    private float CG_Blue_R;
    private float CG_Blue_B;
    private float CG_Blue_G;
    #endregion

    // Start is called before the first frame update
    void Start()
    {
        //Put Json values into the filter list
        myFilterList = JsonUtility.FromJson<FilterList>(FilterData.text);
        myVolume = myFilters.GetComponent<PostProcessVolume>();
        myVolume.profile.TryGetSettings(out myCG);
    }

    // Update is called once per frame
    void Update()
    {
        CheckFilter();
    }

    #region Colorblind Filter Bttns
    public void ArchromatomalyBttnClicked()
    {
        myCG.mixerRedOutRedIn.value = myFilterList.filter[0].Red_R;
        myCG.mixerRedOutGreenIn.value = myFilterList.filter[0].Red_G;
        myCG.mixerRedOutBlueIn.value = myFilterList.filter[0].Red_B;

        myCG.mixerGreenOutRedIn.value = myFilterList.filter[0].Green_R;
        myCG.mixerGreenOutGreenIn.value = myFilterList.filter[0].Green_G;
        myCG.mixerGreenOutBlueIn.value = myFilterList.filter[0].Green_B;

        myCG.mixerBlueOutRedIn.value = myFilterList.filter[0].Blue_R;
        myCG.mixerBlueOutGreenIn.value = myFilterList.filter[0].Blue_G;
        myCG.mixerBlueOutBlueIn.value = myFilterList.filter[0].Blue_B;
    }

    public void ArchromatopsiaBttnClicked()
    {
        myCG.mixerRedOutRedIn.value = myFilterList.filter[1].Red_R;
        myCG.mixerRedOutGreenIn.value = myFilterList.filter[1].Red_G;
        myCG.mixerRedOutBlueIn.value = myFilterList.filter[1].Red_B;

        myCG.mixerGreenOutRedIn.value = myFilterList.filter[1].Green_R;
        myCG.mixerGreenOutGreenIn.value = myFilterList.filter[1].Green_G;
        myCG.mixerGreenOutBlueIn.value = myFilterList.filter[1].Green_B;

        myCG.mixerBlueOutRedIn.value = myFilterList.filter[1].Blue_R;
        myCG.mixerBlueOutGreenIn.value = myFilterList.filter[1].Blue_G;
        myCG.mixerBlueOutBlueIn.value = myFilterList.filter[1].Blue_B;
    }

    public void DeuteranomalyBttnClicked()
    {
        myCG.mixerRedOutRedIn.value = myFilterList.filter[2].Red_R;
        myCG.mixerRedOutGreenIn.value = myFilterList.filter[2].Red_G;
        myCG.mixerRedOutBlueIn.value = myFilterList.filter[2].Red_B;

        myCG.mixerGreenOutRedIn.value = myFilterList.filter[2].Green_R;
        myCG.mixerGreenOutGreenIn.value = myFilterList.filter[2].Green_G;
        myCG.mixerGreenOutBlueIn.value = myFilterList.filter[2].Green_B;

        myCG.mixerBlueOutRedIn.value = myFilterList.filter[2].Blue_R;
        myCG.mixerBlueOutGreenIn.value = myFilterList.filter[2].Blue_G;
        myCG.mixerBlueOutBlueIn.value = myFilterList.filter[2].Blue_B;
    }

    public void DeuteranopiaBttnClicked()
    {
        myCG.mixerRedOutRedIn.value = myFilterList.filter[3].Red_R;
        myCG.mixerRedOutGreenIn.value = myFilterList.filter[3].Red_G;
        myCG.mixerRedOutBlueIn.value = myFilterList.filter[3].Red_B;

        myCG.mixerGreenOutRedIn.value = myFilterList.filter[3].Green_R;
        myCG.mixerGreenOutGreenIn.value = myFilterList.filter[3].Green_G;
        myCG.mixerGreenOutBlueIn.value = myFilterList.filter[3].Green_B;

        myCG.mixerBlueOutRedIn.value = myFilterList.filter[3].Blue_R;
        myCG.mixerBlueOutGreenIn.value = myFilterList.filter[3].Blue_G;
        myCG.mixerBlueOutBlueIn.value = myFilterList.filter[3].Blue_B;
    }

    public void ProtanomalyBttnClicked()
    {
        myCG.mixerRedOutRedIn.value = myFilterList.filter[4].Red_R;
        myCG.mixerRedOutGreenIn.value = myFilterList.filter[4].Red_G;
        myCG.mixerRedOutBlueIn.value = myFilterList.filter[4].Red_B;

        myCG.mixerGreenOutRedIn.value = myFilterList.filter[4].Green_R;
        myCG.mixerGreenOutGreenIn.value = myFilterList.filter[4].Green_G;
        myCG.mixerGreenOutBlueIn.value = myFilterList.filter[4].Green_B;

        myCG.mixerBlueOutRedIn.value = myFilterList.filter[4].Blue_R;
        myCG.mixerBlueOutGreenIn.value = myFilterList.filter[4].Blue_G;
        myCG.mixerBlueOutBlueIn.value = myFilterList.filter[4].Blue_B;
    }

    public void ProtanopiaBttnClicked()
    {
        myCG.mixerRedOutRedIn.value = myFilterList.filter[5].Red_R;
        myCG.mixerRedOutGreenIn.value = myFilterList.filter[5].Red_G;
        myCG.mixerRedOutBlueIn.value = myFilterList.filter[5].Red_B;

        myCG.mixerGreenOutRedIn.value = myFilterList.filter[5].Green_R;
        myCG.mixerGreenOutGreenIn.value = myFilterList.filter[5].Green_G;
        myCG.mixerGreenOutBlueIn.value = myFilterList.filter[5].Green_B;

        myCG.mixerBlueOutRedIn.value = myFilterList.filter[5].Blue_R;
        myCG.mixerBlueOutGreenIn.value = myFilterList.filter[5].Blue_G;
        myCG.mixerBlueOutBlueIn.value = myFilterList.filter[5].Blue_B;
    }

    public void TritanomalyBttnClicked()
    {
        myCG.mixerRedOutRedIn.value = myFilterList.filter[6].Red_R;
        myCG.mixerRedOutGreenIn.value = myFilterList.filter[6].Red_G;
        myCG.mixerRedOutBlueIn.value = myFilterList.filter[6].Red_B;

        myCG.mixerGreenOutRedIn.value = myFilterList.filter[6].Green_R;
        myCG.mixerGreenOutGreenIn.value = myFilterList.filter[6].Green_G;
        myCG.mixerGreenOutBlueIn.value = myFilterList.filter[6].Green_B;

        myCG.mixerBlueOutRedIn.value = myFilterList.filter[6].Blue_R;
        myCG.mixerBlueOutGreenIn.value = myFilterList.filter[6].Blue_G;
        myCG.mixerBlueOutBlueIn.value = myFilterList.filter[6].Blue_B;
    }

    public void TritanopiaBttnClicked()
    {
        myCG.mixerRedOutRedIn.value = myFilterList.filter[7].Red_R;
        myCG.mixerRedOutGreenIn.value = myFilterList.filter[7].Red_G;
        myCG.mixerRedOutBlueIn.value = myFilterList.filter[7].Red_B;

        myCG.mixerGreenOutRedIn.value = myFilterList.filter[7].Green_R;
        myCG.mixerGreenOutGreenIn.value = myFilterList.filter[7].Green_G;
        myCG.mixerGreenOutBlueIn.value = myFilterList.filter[7].Green_B;

        myCG.mixerBlueOutRedIn.value = myFilterList.filter[7].Blue_R;
        myCG.mixerBlueOutGreenIn.value = myFilterList.filter[7].Blue_G;
        myCG.mixerBlueOutBlueIn.value = myFilterList.filter[7].Blue_B;
    }

    public void NoFilterBttnClicked()
    {
        myCG.mixerRedOutRedIn.value = 100;
        myCG.mixerRedOutGreenIn.value = 0;
        myCG.mixerRedOutBlueIn.value = 0;

        myCG.mixerGreenOutRedIn.value = 0;
        myCG.mixerGreenOutGreenIn.value = 100;
        myCG.mixerGreenOutBlueIn.value = 0;

        myCG.mixerBlueOutRedIn.value = 0;
        myCG.mixerBlueOutGreenIn.value = 0;
        myCG.mixerBlueOutBlueIn.value = 100;
    }
    #endregion

    public void LeftOnClick()
    {
        clickCount -= 1;

        if (clickCount < 0)
        {
            clickCount = 0;
        }
    }

    public void RightOnClick()
    {
        clickCount += 1;

        if (clickCount > 8)
        {
            clickCount = 8;
        }
    }

    public void CheckFilter()
    {
        if (clickCount == 0)
        {
            myFilterBttnTxt.text = "No Filter";
            NoFilterBttnClicked();
        }
        else if (clickCount == 1)
        {
            myFilterBttnTxt.text = "Archromatomaly Filter";
            ArchromatomalyBttnClicked();
        }
        else if (clickCount == 2)
        {
            myFilterBttnTxt.text = "Archromatopsia Filter";
            ArchromatopsiaBttnClicked();
        }
        else if (clickCount == 3)
        {
            myFilterBttnTxt.text = "Deuteranomaly Filter";
            DeuteranomalyBttnClicked();
        }
        else if (clickCount == 4)
        {
            myFilterBttnTxt.text = "Deuteranopia Filter";
            DeuteranopiaBttnClicked();
        }
        else if (clickCount == 5)
        {
            myFilterBttnTxt.text = "Protanomaly Filter";
            ProtanomalyBttnClicked();
        }
        else if (clickCount == 6)
        {
            myFilterBttnTxt.text = "Protanopia Filter";
            ProtanopiaBttnClicked();
        }
        else if (clickCount == 7)
        {
            myFilterBttnTxt.text = "Tritanomaly Filter";
            TritanomalyBttnClicked();
        }
        else if (clickCount == 8)
        {
            myFilterBttnTxt.text = "Tritanopia Filter";
            TritanopiaBttnClicked();
        }
    }
}
