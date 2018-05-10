using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.EventSystems;

public class GameController : MonoBehaviour {
	public enum GameState
	{
		BeforeMove,
		Moving,
	}

	public GameState state;
	public GameObject ball;

	[SerializeField]
	GameObject clear_message;

	private bool has_cleared;
	private GameObject[] ice_blocks;
	
	// Use this for initialization
	void Start () {
		state = GameState.BeforeMove;
		has_cleared = false;
		ice_blocks = GameObject.FindGameObjectsWithTag("Ice");
	}

	// Update is called once per frame
	void Update () {
		// Rを押したらリセット
		if (Input.GetKeyDown(KeyCode.R))
		{
			Reset();
		}

		// Spaceでゲーム開始
		if (Input.GetKeyDown(KeyCode.Space))
		{
			if (state == GameState.BeforeMove)
			{
				state = GameState.Moving;
			}
			else if (has_cleared == true)
			{
				Reset();
			}
		}
	}

	void Reset()
	{
		state = GameState.BeforeMove;
		ball.gameObject.GetComponent<Ball>().Reset();
		// 氷リセット
		foreach(GameObject ice in ice_blocks)
		{
			ice.GetComponent<Ice>().Reset();
		}

		foreach (GameObject obj in UnityEngine.Object.FindObjectsOfType(typeof(GameObject)))
		{
			// シーン上に存在するオブジェクトならば処理.
			if (obj.tag == "Water")
			{
				obj.GetComponent<Water>().Reset();
			}
		}

		// クリアテキスト非表示
		clear_message.SetActive(false);

	}

	public void Goal()
	{
		clear_message.SetActive(true);
		has_cleared = true;
	}

	public bool isMoving()
	{
		return state == GameState.Moving;
	}
}
