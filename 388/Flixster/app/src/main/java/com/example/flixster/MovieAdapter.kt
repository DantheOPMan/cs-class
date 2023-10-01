package com.example.flixster

import android.content.Intent
import android.net.Uri
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.Button
import android.widget.ImageView
import android.widget.TextView
import androidx.core.content.ContextCompat
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide

class MovieAdapter(
    private val movies: List<Movie>,
    private val mListener: OnListFragmentInteractionListener?
    )
    : RecyclerView.Adapter<MovieAdapter.MovieViewHolder>()
    {
        override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): MovieViewHolder {
            val view = LayoutInflater.from(parent.context)
                .inflate(R.layout.movie, parent, false)
            return MovieViewHolder(view)
        }

        /**
         * This inner class lets us refer to all the different View elements
         * (Yes, the same ones as in the XML layout files!)
         */
        inner class MovieViewHolder(val mView: View) : RecyclerView.ViewHolder(mView) {
            var mItem: Movie? = null
            val mTitle: TextView = mView.findViewById<View>(R.id.movieTitle) as TextView
            val mDescription: TextView = mView.findViewById<View>(R.id.movieDescription) as TextView
            val mImage: ImageView = mView.findViewById<ImageView>(R.id.movieImage) as ImageView
            override fun toString(): String {
                return "$mTitle '$mDescription'"
            }
        }

        /**
         * This lets us "bind" each Views in the ViewHolder to its' actual data!
         */
        override fun onBindViewHolder(holder: MovieViewHolder, position: Int) {
            val movie = movies[position]

            holder.mItem = movie
            holder.mTitle.text = movie.title
            holder.mDescription.text = movie.overview
            Glide.with(holder.mView)
                .load("https://image.tmdb.org/t/p/w500" + movie.posterPath)
                .centerInside()
                .into(holder.mImage)
            holder.mView.setOnClickListener {
                holder.mItem?.let { movie ->
                    mListener?.onItemClick(movie)
                }
            }
        }


        /**
         * Remember: RecyclerView adapters require a getItemCount() method.
         */
        override fun getItemCount(): Int {
            return movies.size
        }
}