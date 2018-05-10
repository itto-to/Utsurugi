using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Water : MonoBehaviour {

	private bool is_hit_blue;
	private bool is_hit_green;

	Renderer rend;
	Color init_color;
	Color freeze_color;
	GameController gc;

	// Use this for initialization
	void Start () {
		is_hit_blue = false;
		is_hit_green = false;

		rend = gameObject.GetComponent<Renderer>();
		init_color = rend.material.GetColor("_Color");
		freeze_color = new Color(15.0f / 255.0f, 197.0f / 255.0f, 223.0f / 255.0f);
		gc = GameObject.Find("GameController").GetComponent<GameController>();
	}
	
	// Update is called once per frame
	void Update () {

		if (is_hit_blue && is_hit_green && gc.isMoving())
		{
			Freeze();
		}
	}

	void OnTriggerEnter2D(Collider2D coll)
	{
		if (coll.gameObject.tag == "BlueLight")
		{
			is_hit_blue = true;
		}
		if (coll.gameObject.tag == "GreenLight")
		{
			is_hit_green = true;
		}
	}

	void OnTriggerExit2D(Collider2D coll)
	{
		if (coll.gameObject.tag == "BlueLight")
		{
			is_hit_blue = false;
		}
		if (coll.gameObject.tag == "GreenLight")
		{
			is_hit_green = false;
		}
	}

	void Freeze()
	{
		gameObject.GetComponent<BoxCollider2D>().isTrigger = false;
		rend.material.SetColor("_Color", freeze_color);
	}

	public void Reset()
	{
		gameObject.GetComponent<BoxCollider2D>().isTrigger = true;
		rend.material.SetColor("_Color", init_color);
	}
}
