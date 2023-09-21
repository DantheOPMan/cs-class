package com.example.wishlist

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val itemNameText = findViewById<EditText>(R.id.itemNameText)
        val itemUrlText = findViewById<EditText>(R.id.itemUrlText)
        val itemPriceText = findViewById<EditText>(R.id.itemPriceText)
        var itemsRv = findViewById<RecyclerView>(R.id.itemsRv)
        emails = EmailFetcher.getEmails()
        val adapter = EmailAdapter(emails)
        emailsRV.adapter = adapter
        emailsRV.layoutManager = LinearLayoutManager(this)
        findViewById<Button>(R.id.loadMoreBtn).setOnClickListener {
            // Fetch next 5 emails and display in RecyclerView
            val newEmails = EmailFetcher.getNext5Emails()
            (emails as MutableList<Email>).addAll(newEmails)
            adapter.notifyDataSetChanged()
        }
        itemNameText.setOnFocusChangeListener { _, hasFocus ->
            if (hasFocus) {
                itemNameText.text.clear()
            }
        }
        itemUrlText.setOnFocusChangeListener { _, hasFocus ->
            if (hasFocus) {
                itemUrlText.text.clear()
            }
        }
        itemPriceText.setOnFocusChangeListener { _, hasFocus ->
            if (hasFocus) {
                itemPriceText.text.clear()
            }
        }
    }
}