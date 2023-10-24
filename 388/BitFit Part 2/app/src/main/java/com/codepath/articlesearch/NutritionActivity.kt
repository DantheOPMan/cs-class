package com.codepath.articlesearch

import android.annotation.SuppressLint
import android.content.Intent
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.recyclerview.widget.RecyclerView


class NutritionActivity : AppCompatActivity() {
    // Declare a variable to hold a reference to the RecyclerView in the layout.
    private lateinit var nutritionRV : RecyclerView

    @SuppressLint("MissingInflatedId")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_nutrition)
        // Get references to the views for nutrition name input, calorie count input and the button to save the input.
        val nutritionInputET : EditText = findViewById(R.id.nutritionInput)
        val calorieCountET : EditText = findViewById(R.id.caloriesInput)
        val recordInputBt : Button = findViewById<Button>(R.id.inputButton)
        // Add a click listener to the "recordInputBt" button.
        recordInputBt.setOnClickListener(View.OnClickListener {
            // When the button is clicked, create a new Intent to return the entered nutrition data to the calling activity.
            val resultIntent = Intent()
            // Pass the entered nutrition data as an extra with the Intent.
            resultIntent.putExtra("result", Nutrition(nutritionName = nutritionInputET.text.toString(),
                calorieCount = calorieCountET.text.toString()))
            // Set the result code and the result Intent to return to the calling activity.
            setResult(RESULT_OK, resultIntent)
            finish()
        })
    }
}