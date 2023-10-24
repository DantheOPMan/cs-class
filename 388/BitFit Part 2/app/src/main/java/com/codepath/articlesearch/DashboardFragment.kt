package com.codepath.articlesearch

import android.annotation.SuppressLint
import android.content.Context
import android.os.Bundle
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.TextView
import androidx.fragment.app.Fragment
import androidx.lifecycle.lifecycleScope
import kotlinx.coroutines.Dispatchers
import kotlinx.coroutines.launch


class DashboardFragment : Fragment() {
    // These are the class variables that hold the average,
    // minimum, and maximum values.
    private var averageValue: String? = null
    private var minValue: String? = null
    private var maxValue: String? = null
    // These are the TextView variables for the average,
    // minimum, and maximum values.
    lateinit var averageValueTV: TextView
    lateinit var minValueTV: TextView
    lateinit var maxValueTV: TextView
    // This is an interface for the OnClearListener.
    private var listener: OnClearListener? = null
    // This is an interface that has the onClearData function.
    interface OnClearListener {
        fun onClearData()
    }
    // This is the onAttach function for the context.
    override fun onAttach(context: Context) {
        super.onAttach(context)
        listener = context as OnClearListener
    }
    // This is the onCreate function for the class that sets the
    // values of the average, minimum, and maximum.
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        arguments?.let {
            averageValue  = it.getString(AVERAGE)
            minValue = it.getString(MINIMUM)
            maxValue = it.getString(MAXIMUM)
        }
    }
    @SuppressLint("MissingInflatedId")
    override fun onCreateView(
        inflater: LayoutInflater, container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View? {
        // This creates a view with the layout from the dashboard_fragment XML file.
        val view: View = inflater.inflate(R.layout.dashboard_fragment, container, false)
        // This assigns the TextView variables to their corresponding views.
        averageValueTV = view.findViewById<TextView>(R.id.avgCaloriesValueTV)
        minValueTV = view.findViewById<TextView>(R.id.minCaloriesValueTV)
        maxValueTV = view.findViewById<TextView>(R.id.maxCaloriesValueTV)
        // This updates the dashboard with the current average, minimum, and maximum values.
        updateDashboard(averageValue ?:"0", minValue ?: "0", maxValue ?: "0")

        val clearDataBtn = view.findViewById<Button>(R.id.clearDataButton)
        // This sets an OnClickListener for the clearDataButton that clears the data when clicked.
        clearDataBtn.setOnClickListener(View.OnClickListener {
            lifecycleScope.launch(Dispatchers.IO) {
                (activity?.application as NutritionApplication).db.NutritionDao().deleteAll()
                listener?.onClearData()
            }
            updateDashboard("0","0","0")
        })
        return view
    }
    // This function updates the dashboard with new average, minimum, and maximum values.
    fun updateDashboard(average: String, minimum: String, maximum: String) {
        averageValueTV.text = average
        minValueTV.text = minimum
        maxValueTV.text = maximum
    }
    // This is a companion object for the DashboardFragment class.
    companion object {
        // This function creates a new instance of the DashboardFragment class with the given average,
        // minimum, and maximum values.
        @JvmStatic
        fun newInstance(average: String, minimum: String, maximum: String) =
            DashboardFragment().apply {
                arguments = Bundle().apply {
                    putString(AVERAGE, average)
                    putString(MINIMUM, minimum)
                    putString(MAXIMUM, maximum)
                }
            }
    }
}