package com.example.wishlist

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class MainActivity : AppCompatActivity() {
    lateinit var items: List<Item>
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val itemNameText = findViewById<EditText>(R.id.itemNameText)
        val itemUrlText = findViewById<EditText>(R.id.itemUrlText)
        val itemPriceText = findViewById<EditText>(R.id.itemPriceText)
        var itemsRv = findViewById<RecyclerView>(R.id.itemsRv)
        items = ArrayList()
        val adapter = ItemAdapter(items)
        itemsRv.adapter = adapter
        itemsRv.layoutManager = LinearLayoutManager(this)
        findViewById<Button>(R.id.button).setOnClickListener {
            val newItem = Item(itemNameText.text,itemPriceText.text, itemUrlText.text)
            (items as MutableList<Item>).add(newItem)
            adapter.notifyDataSetChanged()

            itemNameText.text = null
            itemUrlText.text = null
            itemPriceText.text = null

        }
    }
}