package com.example.lab2

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView

class MainActivity : AppCompatActivity() {
    lateinit var emails: List<Email>
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        var emailsRV = findViewById<RecyclerView>(R.id.emailsRv)
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

    }
}