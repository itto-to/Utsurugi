using UnityEngine;

public class Ball : MonoBehaviour, IReset {

	public float upward_speed = 1.0f;
	public float buoyancy = 15.0f;
	public float max_speed = 20.0f;

	private Rigidbody2D rb;
	private Vector3 init_pos;
	private bool is_hit_red;
	private bool is_hit_green;
	private bool is_hit_blue;

	[SerializeField]
	GameObject game_controller;

	// Use this for initialization
	void Start ()
	{
		rb = this.GetComponent<Rigidbody2D>();
		init_pos = rb.position;
		is_hit_red   = false;
		is_hit_green = false;
		is_hit_blue  = false;
	}

	// Update is called once per frame
	void Update()
	{
		if (!game_controller.GetComponent<GameController>().isMoving())
		{
			rb.velocity = Vector3.zero;
			rb.angularVelocity = 0.0f;
			rb.isKinematic = true;
			return;
		}
		else
		{
			rb.isKinematic = false;
		}

		// ライトとの当たり判定
		CheckHitLight();
	}

	void OnTriggerEnter2D(Collider2D coll)
	{
		// ゴールとの当たり判定
		CheckHitGoal(coll);

		// ライトとの当たり判定
		if (coll.gameObject.tag == "RedLight")
		{
			is_hit_red = true;
		}

		if (coll.gameObject.tag == "GreenLight")
		{
			is_hit_green = true;
		}

		if (coll.gameObject.tag == "BlueLight")
		{
			is_hit_blue = true;
		}
	}

	void OnTriggerExit2D(Collider2D coll)
	{
		if (coll.gameObject.tag == "RedLight")
		{
			is_hit_red = false;
		}

		if (coll.gameObject.tag == "GreenLight")
		{
			is_hit_green = false;
		}

		if (coll.gameObject.tag == "BlueLight")
		{
			is_hit_blue = false;
		}
	}

	void OnTriggerStay2D(Collider2D coll)
	{
		if (coll.gameObject.tag == "Water")
		{

		}
	}

	void CheckHitGoal(Collider2D coll)
	{
		if (coll.gameObject.tag == "Goal")
		{
			game_controller.GetComponent<GameController>().Goal();
		}
	}

	void CheckHitLight()
	{
		if (is_hit_red && is_hit_green && is_hit_blue)
		{
			// 何も起きない
		}
		else if (is_hit_red && is_hit_green)
		{
			// 加速
			rb.velocity = rb.velocity * 2.0f;
			if (rb.velocity.magnitude > max_speed)
			{
				rb.velocity = rb.velocity.normalized * max_speed;
			}
		}
		else if (is_hit_blue && is_hit_red)
		{
			// 重力反転
			Vector2 local_gravity = new Vector2(0.0f, 9.8f);
			rb.AddForce(local_gravity * 2, ForceMode2D.Force);
		}
		else if (is_hit_blue)
		{
			// 水中
			rb.AddForce(new Vector2(0.0f, 4.9f), ForceMode2D.Force);
		}
		else if (is_hit_green)
		{
			// ゆっくり上昇
			rb.velocity = new Vector2(rb.velocity.x, upward_speed);
		}
	}

	public void Reset()
	{
		rb.position = init_pos;
		rb.velocity = Vector3.zero;
	}
}
