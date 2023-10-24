package com.codepath.articlesearch

import android.annotation.SuppressLint
import android.os.Bundle
import androidx.fragment.app.Fragment
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import androidx.lifecycle.lifecycleScope
import androidx.recyclerview.widget.DividerItemDecoration
import androidx.recyclerview.widget.LinearLayoutManager
import androidx.recyclerview.widget.RecyclerView
import kotlinx.coroutines.launch


class LogFragment : Fragment() {
    // Declare UI components
    private lateinit var nutritionRecyclerView: RecyclerView
    lateinit var nutritionAdapter: NutritionAdapter
    // Declare data
    val nutritionList = mutableListOf<Nutrition>()

    @SuppressLint("MissingInflatedId")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        val view =  inflater.inflate(R.layout.log_fragment, container, false)

        // Setup/Initialize RecyclerView and its adapter
        nutritionRecyclerView = view.findViewById(R.id.nutritionRV)
        nutritionAdapter = NutritionAdapter(view.context, nutritionList)
        nutritionRecyclerView.adapter = nutritionAdapter
        nutritionRecyclerView.layoutManager = LinearLayoutManager(view.context).also {
            val dividerItemDecorator = DividerItemDecoration(view.context, it.orientation)
            nutritionRecyclerView.addItemDecoration(dividerItemDecorator)
        }
        // Load logs from database and display observe nutrition data changes in RecyclerView
        lifecycleScope.launch{
            (activity?.application as NutritionApplication).db.NutritionDao().getAll().collect{
                    databaseList -> databaseList.map { entity ->
                Nutrition(
                    entity.nutritionName,
                    entity.calorieCount
                )
            }.also { mappedList ->
                nutritionList.clear()
                nutritionList.addAll(mappedList)
                nutritionAdapter.notifyDataSetChanged() }
            }
        }

        return view
    }
}