using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerControl : MonoBehaviour {

    public KeyCode up, down, left, right;

    public int posX, posY;
    int oldX = 0, oldY = 0;

    public bool mode = true;
    public bool onMirror = false;

    public bool keyFlag, doorFlag;

    GameObject stageInfo, mirrorInfo, key, door;

    SpriteRenderer sr;

	// Use this for initialization
	void Start () {
        posX = 0;
        posY = 0;
        mode = true;

        keyFlag = false;
        doorFlag = false;

        stageInfo = GameObject.Find("MapInfo");
        mirrorInfo = GameObject.Find("MirrorSystem");
        key = GameObject.Find("Key");
        door = GameObject.Find("Door");

        sr = GetComponent<SpriteRenderer>();
	}

    // Update is called once per frame
    void Update() {

        oldX = posX;
        oldY = posY;

        if(mode == mirrorInfo.GetComponent<MirrorControl>().mirrorMode)
        {
            if (posX >= mirrorInfo.GetComponent<MirrorControl>().mPosX && posX < (mirrorInfo.GetComponent<MirrorControl>().mPosX + 3))
            {
                onMirror = true;
            }
            else
            {
                onMirror = false;
            }
        }
        else
        {
            onMirror = false;
        }

        if (mode == true && stageInfo.GetComponent<StageInfo>().UpMapW[posX + posY * 10] == true)
        {
            if (Input.GetKeyDown(up) && posY < 3)
            {
                posY++;
                //if (stageInfo.GetComponent<StageInfo>().UpMap[posY * 10 + posX] == true)
                if (stageInfo.GetComponent<StageInfo>().GetWalk(mode, (posY * 10 + posX)) == true)
                {
                    transform.position = new Vector3((float)(posX - 5 + (posY * 0.3)), (float)(0.8 + (posY * 0.92)), transform.position.z);
                }
                else
                {
                    posX = oldX;
                    posY = oldY;
                }
            }
            if (Input.GetKeyDown(down) && posY > 0)
            {
                posY--;
                if (stageInfo.GetComponent<StageInfo>().GetWalk(mode, (posY * 10 + posX)) == true)
                {
                    transform.position = new Vector3((float)(posX - 5 + (posY * 0.3)), (float)(0.8 + (posY * 0.92)), transform.position.z);
                }
                else
                {
                    posX = oldX;
                    posY = oldY;
                }
            }
            if (Input.GetKeyDown(left) && posX > 0)
            {
                posX--;
                if (stageInfo.GetComponent<StageInfo>().GetWalk(mode, (posY * 10 + posX)) == true)
                {
                    transform.position = new Vector3((float)(posX - 5 + (posY * 0.3)), (float)(0.8 + (posY * 0.92)), transform.position.z);
                }
                else
                {
                    posX = oldX;
                    posY = oldY;
                }
            }
            if (Input.GetKeyDown(right) && posX < 9)
            {
                posX++;
                if (stageInfo.GetComponent<StageInfo>().GetWalk(mode, (posY * 10 + posX)) == true)
                {
                    transform.position = new Vector3((float)(posX - 5 + (posY * 0.3)), (float)(0.8 + (posY * 0.92)), transform.position.z);
                }
                else
                {
                    posX = oldX;
                    posY = oldY;
                }
            }
            /*
            if (stageInfo.GetComponent<StageInfo>().UpMap[posY * 10 + posX] == true)
            {
                transform.position = new Vector3((float)(posX - 5 + (posY * 0.3)), (float)(0.8 + (posY * 0.92)), transform.position.z);
            }
            else
            {
                posX = oldX;
                posY = oldY;
            }*/
        }

        if (mode == false && stageInfo.GetComponent<StageInfo>().DownMapW[posX + posY * 10] == true)
        {
            if (Input.GetKeyDown(up) && posY > 0)
            {
                posY--;
                //if (stageInfo.GetComponent<StageInfo>().UpMap[posY * 10 + posX] == true)
                if (stageInfo.GetComponent<StageInfo>().GetWalk(mode, (posY * 10 + posX)) == true)
                {
                    transform.position = new Vector3((float)(posX - 5 + (posY * 0.3)), (float)(-(0.8 + (posY * 0.92))), transform.position.z);
                }
                else
                {
                    posX = oldX;
                    posY = oldY;
                }
            }
            if (Input.GetKeyDown(down) && posY < 3)
            {
                posY++;
                if (stageInfo.GetComponent<StageInfo>().GetWalk(mode, (posY * 10 + posX)) == true)
                {
                    transform.position = new Vector3((float)(posX - 5 + (posY * 0.3)), (float)(-(0.8 + (posY * 0.92))), transform.position.z);
                }
                else
                {
                    posX = oldX;
                    posY = oldY;
                }
            }
            if (Input.GetKeyDown(left) && posX > 0)
            {
                posX--;
                if (stageInfo.GetComponent<StageInfo>().GetWalk(mode, (posY * 10 + posX)) == true)
                {
                    transform.position = new Vector3((float)(posX - 5 + (posY * 0.3)), (float)(-(0.8 + (posY * 0.92))), transform.position.z);
                }
                else
                {
                    posX = oldX;
                    posY = oldY;
                }
            }
            if (Input.GetKeyDown(right) && posX < 9)
            {
                posX++;
                if (stageInfo.GetComponent<StageInfo>().GetWalk(mode, (posY * 10 + posX)) == true)
                {
                    transform.position = new Vector3((float)(posX - 5 + (posY * 0.3)), (float)(-(0.8 + (posY * 0.92))), transform.position.z);
                }
                else
                {
                    posX = oldX;
                    posY = oldY;
                }
            }
        }

        if(stageInfo.GetComponent<StageInfo>().CheckKey(mode, posX + posY * 10) == true)
        {
            keyFlag = true;
            //GameObject.Find("Key").SetActive(false);
            key.gameObject.SetActive(false);
            mirrorInfo.GetComponent<MirrorControl>().MakeMirror();
        }

        if (stageInfo.GetComponent<StageInfo>().CheckDoor(mode, posX + posY * 10) == true && keyFlag == true)
        {
            doorFlag = true;
            door.gameObject.SetActive(false);
            mirrorInfo.GetComponent<MirrorControl>().MakeMirror();
        }




    }

    public void FlipPlayer()
    {
        if(mode == true)
        {
            sr.flipY = true;
            transform.position = new Vector3(transform.position.x, -transform.position.y, transform.position.z);
            mode = false;
        }

        else
        {
            sr.flipY = false;
            transform.position = new Vector3(transform.position.x, -transform.position.y, transform.position.z);
            mode = true;
        }
    }

}
