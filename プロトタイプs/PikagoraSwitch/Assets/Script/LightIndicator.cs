using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class LightIndicator : MonoBehaviour {

	Renderer rend;

	// Use this for initialization
	void Start () {
		rend = GetComponent<Renderer>();
	}
	
	// Update is called once per frame
	void Update () {
		int light_no = GetComponentInParent<LightController>().lightNo;
		//Renderer rend = GetComponent<Renderer>();
		
		switch (light_no)
		{
			case 0:
				rend.material.SetColor("_Color", Color.red);
				break;
			case 1:
				rend.material.SetColor("_Color", Color.green);
				break;
			case 2:
				rend.material.SetColor("_Color", Color.blue);
				break;
		}
	}
}
