using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Ice : MonoBehaviour, IReset {

	GameController gc;

	// Use this for initialization
	void Start () {
		gc = GameObject.Find("GameController").GetComponent<GameController>();
	}
	
	// Update is called once per frame
	void Update () {
	}

	void OnTriggerStay2D(Collider2D coll)
	{
		if (coll.gameObject.tag == "RedLight" && gc.isMoving())
		{
			// 赤い光にスタート中にあたったら消す
			gameObject.SetActive(false);
		}
	}

	public void Reset()
	{
		gameObject.SetActive(true);
	}
}
