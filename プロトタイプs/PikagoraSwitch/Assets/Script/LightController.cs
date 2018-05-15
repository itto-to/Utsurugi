using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightController : MonoBehaviour {
	private const int kMaxLight = 3;

	public float speed = 0.001f;
	public GameObject[] lights = new GameObject[kMaxLight];
	public int lightNo;
	public GameObject selectedLight;

	GameObject game_controller;

	// Use this for initialization
	void Start () {
		lightNo = 0;
		selectedLight = lights[0];

		game_controller = GameObject.Find("GameController");
	}
	
	// Update is called once per frame
	void Update () {
		// ゲーム実行中なら動かせない
		if (game_controller.GetComponent<GameController>().state == GameController.GameState.Moving)
		{
			return;
		}

		// 操作ライト変更
		if (Input.GetKeyDown(KeyCode.E))
		{
			ChangeLight();
		}

		// ライト移動
		Vector3 move = new Vector3();

		if (Input.GetKey(KeyCode.W))
		{
			move.y = 1.0f;
		}
		else if (Input.GetKey(KeyCode.S))
		{
			move.y = -1.0f;
		}

		if (Input.GetKey(KeyCode.A))
		{
			move.x = -1.0f;
		}
		else if (Input.GetKey(KeyCode.D))
		{
			move.x = 1.0f;
		}
		move = move.normalized * speed;
		selectedLight.transform.Translate(move);
	}

	private void ChangeLight()
	{
		lightNo = (lightNo + 1) % kMaxLight;
		selectedLight = lights[lightNo];
	}
}
