package com.codepath.articlesearch

import android.content.Context
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView

class NutritionAdapter(private val context: Context, private val nutrition:List<Nutrition>) : RecyclerView.Adapter<NutritionAdapter.ViewHolder>(){

    // onCreateViewHolder creates a ViewHolder and sets up the view
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        // inflate the view
        val view = LayoutInflater.from(context).inflate(R.layout.nutrition_item, parent, false)
        // create a new ViewHolder with the inflated view
        return ViewHolder(view)
    }
    // onBindViewHolder binds the data to the ViewHolder
    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        // get the Nutrition object at the current position
        val nutrition = nutrition[position]
        // bind the data to the ViewHolder
        holder.bind(nutrition)
    }
    // getItemCount returns the number of items in the list
    override fun getItemCount(): Int {
        return nutrition.size
    }
    // inner class ViewHolder represents each item in the list
    inner class ViewHolder(itemView:View) : RecyclerView.ViewHolder(itemView), View.OnClickListener{
        // create references to the views in the ViewHolder
        private val foodTV : TextView = itemView.findViewById(R.id.foodNameTV)
        private val calorieCount : TextView = itemView.findViewById(R.id.calorieCountTV)

        // initialize the OnClickListener for the ViewHolder
        init {
            itemView.setOnClickListener(this)
        }
        // bind the data to the views in the ViewHolder
        fun bind(nutrition: Nutrition) {
            foodTV.text = nutrition.nutritionName
            calorieCount.text = nutrition.calorieCount
        }
        // empty onClick method required by the OnClickListener interface
        override fun onClick(p0: View?) {
        }
    }
}