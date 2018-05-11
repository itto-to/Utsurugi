using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class StageInfo : MonoBehaviour {

    public bool[] UpMap;

    public bool[] DownMap;

    public bool[] UpMapW, DownMapW;

    public bool keyM, doorM;
    public int keyI, doorI;

    /*void Awake()
    {
        UpMapW = new bool[40];
        DownMap = new bool[40];
    }*/

    // Use this for initialization
    void Start () {
        WalkRangeReset();

        keyM = false;
        doorM = true;

        keyI = 36;
        doorI = 37;

	}
	
	// Update is called once per frame
	void Update () {
		
	}

    public void WalkRangeReset()
    {
        for (int i = 0; i < 40; i++)
        {
            UpMapW[i] = UpMap[i];
            DownMapW[i] = DownMap[i];
        }
    }

    public void SetWalk(bool mode, bool active, int index)
    {
        if (mode == true)
        {
            UpMapW[index] = active;
        }
        else
        {
            DownMapW[index] = active;
        }
    }

    public bool GetWalk(bool mode, int index)
    {
        if(mode == true)
        {
            return UpMapW[index];
        }
        else
        {
            return DownMapW[index];
        }

    }

    public bool CheckKey(bool mode, int index)
    {
        if(keyM == mode && keyI == index)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    public bool CheckDoor(bool mode, int index)
    {
        if (doorM == mode && doorI == index)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}
