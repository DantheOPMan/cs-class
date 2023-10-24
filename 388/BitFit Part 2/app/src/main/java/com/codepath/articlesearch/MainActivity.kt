package com.codepath.articlesearch

import android.annotation.SuppressLint
import android.content.Intent
import android.os.Bundle
import android.view.View
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import androidx.lifecycle.lifecycleScope
import com.google.android.material.bottomnavigation.BottomNavigationView
import kotlinx.coroutines.Dispatchers.IO
import kotlinx.coroutines.launch

const val AVERAGE: String = "AVERAGE"
const val MINIMUM: String = "MINIMUM"
const val MAXIMUM: String = "MAXIMUM"

class MainActivity : AppCompatActivity(), DashboardFragment.OnClearListener {
    // LogFragment and DashboardFragment instances used to switch between views
    private lateinit var nutritionLogFragment: LogFragment
    private lateinit var nutritionDashboardFragment: DashboardFragment

    @SuppressLint("MissingInflatedId")
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        // Initialize the LogFragment and DashboardFragment
        nutritionLogFragment = LogFragment()
        nutritionDashboardFragment = DashboardFragment()
        // Set the initial view to the LogFragment
        supportFragmentManager.beginTransaction()
            .replace(R.id.nutritionFrameLayout, nutritionLogFragment, "log_fragment").commit()
        // Set the OnClickListener for the "Add Nutrition" button
        val addNutritionBtn = findViewById<Button>(R.id.addNutritionBtn)
        addNutritionBtn.setOnClickListener(View.OnClickListener {
            val intent = Intent(this, NutritionActivity::class.java)
            startActivityForResult(intent, 1)
        })
        // Set the listener for the bottom navigation bar to switch between views
        val bottomNavigationView: BottomNavigationView = findViewById(R.id.bottomNavigationView)
        bottomNavigationView.setOnItemSelectedListener { item ->
            when (item.itemId) {
                R.id.logView -> {
                    supportFragmentManager.beginTransaction()
                        .replace(R.id.nutritionFrameLayout, nutritionLogFragment, "log_fragment").commit()
                    true
                }
                R.id.dashboardView -> {
                    // Calculate dashboard values and pass them to the DashboardFragment
                    val (average, min, max) = calculateDashboardValues()
                    val bundle = Bundle()
                    bundle.putString(AVERAGE, average.toString())
                    bundle.putString(MINIMUM, min.toString())
                    bundle.putString(MAXIMUM, max.toString())
                    nutritionDashboardFragment.arguments = bundle

                    // Switch to the DashboardFragment view
                    supportFragmentManager.beginTransaction()
                        .replace(R.id.nutritionFrameLayout, nutritionDashboardFragment, "dashboard_fragment").commit()
                    true
                }
                else -> {
                    true
                }
            }
        }
    }
    // Calculates the average, minimum, and maximum calorie values of the Nutrition items in the LogFragment
    private fun calculateDashboardValues(): Triple<Int, Int, Int> {
        val nutritionCalories: ArrayList<Int> = ArrayList()
        for (nutrition in nutritionLogFragment.nutritionList) {
            nutrition.calorieCount?.toInt()?.let { nutritionCalories.add(it) }
        }
        // If there are no Nutrition items in the LogFragment, return 0 for all values
        if (nutritionCalories.size == 0) {
            return Triple(0, 0, 0)
        }
        // Calculate the average, minimum, and maximum calorie values and return them as a Triple
        return Triple(
            nutritionCalories.average().toInt(),
            nutritionCalories.min(),
            nutritionCalories.max()
        )
    }
    override fun onActivityResult(requestCode: Int, resultCode: Int, data: Intent?) {
        super.onActivityResult(requestCode, resultCode, data)
        if (requestCode == 1) {
            if (resultCode == RESULT_OK) {
                val nutritionResult = data?.getSerializableExtra("result") as Nutrition
                nutritionLogFragment.nutritionList.add(nutritionResult)
                nutritionLogFragment.nutritionAdapter.notifyDataSetChanged()

                // If the DashboardFragment is currently visible, update it with the new
                if (supportFragmentManager.findFragmentByTag("dashboard_fragment")?.isVisible == true) {
                    var (average, min, max) = calculateDashboardValues()

                    nutritionDashboardFragment.updateDashboard(
                        average.toString(),
                        min.toString(),
                        max.toString()
                    )
                }
                // Launch a coroutine in the IO context to insert the new
                // NutritionEntity into the database
                lifecycleScope.launch(IO) {
                    (application as NutritionApplication).db.NutritionDao().insert(
                        NutritionEntity(
                            nutritionName = nutritionResult.nutritionName,
                            calorieCount = nutritionResult.calorieCount
                        )
                    )
                }
            }
        }
    }
    // This function is called when the "Clear" button is pressed in
    // the DashboardFragment, and it clears the nutritionList
    // and notifies the adapter of the LogFragment to refresh the list
    override fun onClearData() {
        nutritionLogFragment.nutritionList.clear()
        nutritionLogFragment.nutritionAdapter.notifyDataSetChanged()
    }
}