package com.codepath.articlesearch

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class NutritionAdapter(private val context: Context, private val nutrition:List<Nutrition>) : RecyclerView.Adapter<NutritionAdapter.NutritionViewHolder>(){

    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): NutritionViewHolder{
        val view = LayoutInflater.from(context).inflate(R.layout.nutrition_item, parent, false)
        return NutritionViewHolder(view)
    }

    override fun onBindViewHolder(holder: NutritionViewHolder, position: Int) {
        val nutrition = nutrition[position]
        holder.bind(nutrition)
    }

    override fun getItemCount(): Int {
        return nutrition.size
    }

    inner class NutritionViewHolder(itemView:View) : RecyclerView.ViewHolder(itemView), View.OnClickListener{
        private val nutritionNameTV : TextView = itemView.findViewById(R.id.nutritionNameTV)
        private val calorieCountTV : TextView = itemView.findViewById(R.id.calorieCountTV)
        init
        {
            itemView.setOnClickListener(this)
        }

        fun bind(nutrition: Nutrition)
        {
            nutritionNameTV.text = nutrition.nutritionName
            calorieCountTV.text = nutrition.calorieCount
        }

        override fun onClick(p0: View?) {
            // No operation
        }
    }
}