package com.codepath.articlesearch

import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import android.widget.EditText
import androidx.appcompat.app.AppCompatActivity
import androidx.recyclerview.widget.RecyclerView


class NutritionActivity : AppCompatActivity() {
    private lateinit var nutritionRv : RecyclerView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_add_nutrition)
        val nutritionInputET : EditText = findViewById(R.id.nutritionInput)
        val calorieCountET : EditText = findViewById(R.id.caloriesInput)
        val recordInputBt : Button = findViewById(R.id.inputButton)

        recordInputBt.setOnClickListener(View.OnClickListener {

            val resultIntent = Intent()
            resultIntent.putExtra("result", Nutrition(nutritionName = nutritionInputET.text.toString(), calorieCount = calorieCountET.text.toString()))
            setResult(RESULT_OK, resultIntent)
            finish()
        })
    }
}