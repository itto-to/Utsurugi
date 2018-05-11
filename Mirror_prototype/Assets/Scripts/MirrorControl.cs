using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class MirrorControl : MonoBehaviour {

    public KeyCode left, right, up, down;

    public bool mirrorMode = true;

    public int mPosX, mPosY;

    int oldmPosX = 0, oldmPosY = 0;

    int mirrorRangeX = 3, mirrorRangeY = 4;

    GameObject stageInfo, player;


    // Use this for initialization
    void Start () {
        mirrorMode = true;
        mPosX = 2;
        oldmPosX = mPosX;
        mPosY = 0;
        oldmPosY = mPosY;

        stageInfo = GameObject.Find("MapInfo");
        player = GameObject.Find("Player");

        MakeMirror();

	}
	
	// Update is called once per frame
	void Update () {
        oldmPosX = mPosX;
        oldmPosY = mPosY;

        if(mirrorMode == true)
        {
            if(Input.GetKeyDown(left) && mPosX > 0)
            {
                mPosX--;
                transform.position = new Vector3((float)(mPosX-2), transform.position.y, transform.position.z);
                MakeMirror();
            }
            if (Input.GetKeyDown(right) && mPosX + mirrorRangeX - 1 < 9)
            {
                mPosX++;
                transform.position = new Vector3((float)(mPosX-2), transform.position.y, transform.position.z);
                MakeMirror();
            }
            if (Input.GetKeyDown(down))
            {
                FlipMirror();
            }
        }

        if (mirrorMode == false)
        {
            if (Input.GetKeyDown(left) && mPosX > 0)
            {
                mPosX--;
                transform.position = new Vector3((float)(mPosX - 2), transform.position.y, transform.position.z);
                MakeMirror();
            }
            if (Input.GetKeyDown(right) && mPosX + mirrorRangeX - 1 < 9)
            {
                mPosX++;
                transform.position = new Vector3((float)(mPosX - 2), transform.position.y, transform.position.z);
                MakeMirror();
            }
            if (Input.GetKeyDown(up))
            {
                FlipMirror();
            }
        }

    }

    public void MakeMirror()
    {
        stageInfo.GetComponent<StageInfo>().WalkRangeReset();

        for(int i = 0; i < mirrorRangeX * mirrorRangeY * 2; i++)
        {
            transform.GetChild(i).gameObject.SetActive(false);
        }
        

        if(mirrorMode == true)
        {

            for (int j = 0; j < mirrorRangeY; j++)
            {
                for (int i = 0; i < mirrorRangeX; i++)
                {
                    stageInfo.GetComponent<StageInfo>().SetWalk(true, false, (mPosX + i) + ((mPosY + j) * 10));
                }

            }

                    for (int j = 0; j < mirrorRangeY; j++)
            {
                for(int i = 0; i < mirrorRangeX; i++)
                {
                    if (stageInfo.GetComponent<StageInfo>().DownMap[(mPosX + i) + ((mPosY + j) * 10)] == true)
                    {
                        transform.GetChild(i + j * mirrorRangeX).gameObject.SetActive(true);
                        stageInfo.GetComponent<StageInfo>().SetWalk(true, true, (mPosX + i) + ((mPosY + j) * 10));

                    }
                }
                
            }

        }

        if (mirrorMode == false)
        {
            for (int j = 0; j < mirrorRangeY; j++)
            {
                for (int i = 0; i < mirrorRangeX; i++)
                {
                    stageInfo.GetComponent<StageInfo>().SetWalk(false, false, (mPosX + i) + ((mPosY + j) * 10));
                }

            }

            for (int j = 0; j < mirrorRangeY; j++)
            {
                for (int i = 0; i < mirrorRangeX; i++)
                {
                    if (stageInfo.GetComponent<StageInfo>().UpMap[(mPosX + i) + ((mPosY + j) * 10)] == true)
                    {
                        transform.GetChild(12 + i + j * mirrorRangeX).gameObject.SetActive(true);
                        stageInfo.GetComponent<StageInfo>().SetWalk(false, true, (mPosX + i) + ((mPosY + j) * 10));

                    }
                }

            }

        }
    }

    public void FlipMirror()
    {
        if(mirrorMode == true)
        {
            mirrorMode = false;

            for(int i = 0; i < mirrorRangeX * mirrorRangeY; i++)
            {
                transform.Find("Mirror").GetChild(i).gameObject.SetActive(false);
                transform.Find("Mirror").GetChild(i + mirrorRangeX * mirrorRangeY).gameObject.SetActive(true);
            }

            MakeMirror();

        }
        else
        {
            mirrorMode = true;

            for (int i = 0; i < mirrorRangeX * mirrorRangeY; i++)
            {
                transform.Find("Mirror").GetChild(i).gameObject.SetActive(true);
                transform.Find("Mirror").GetChild(i + mirrorRangeX * mirrorRangeY).gameObject.SetActive(false);
            }

            MakeMirror();
        }

        if (player.GetComponent<PlayerControl>().onMirror == true)
        {
            player.GetComponent<PlayerControl>().FlipPlayer();
        }

    }

}
