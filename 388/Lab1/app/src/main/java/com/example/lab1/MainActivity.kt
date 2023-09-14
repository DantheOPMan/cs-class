package com.example.lab1

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.TextView

class MainActivity : AppCompatActivity() {
    var counter = 0
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val button = findViewById<Button>(R.id.button)
        val button2 = findViewById<Button>(R.id.button2)
        val textView = findViewById<TextView>(R.id.textView)

        button.setOnClickListener{
            counter += 1
            textView.text = counter.toString()
            if (counter >= 100){
                button2.visibility= View.VISIBLE
                button2.setOnClickListener{
                    button.text = "Add 2"
                    button.setOnClickListener {
                        counter += 2
                        textView.text = counter.toString()
                    }
                    button2.visibility = View.INVISIBLE
                }

            }
        }

    }
}