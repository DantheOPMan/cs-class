package com.example.flixster2

import android.content.Context
import android.content.Intent
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.ImageView
import android.widget.TextView
import androidx.recyclerview.widget.RecyclerView
import com.bumptech.glide.Glide

const val TVSHOW_EXTRA = "TVSHOW_EXTRA"
private const val TAG = "PersonAdapter"
class TVShowAdapter(private val context: Context, private val articles: List<TVShow>) :
    RecyclerView.Adapter<TVShowAdapter.ViewHolder>()  {
    override fun onCreateViewHolder(parent: ViewGroup, viewType: Int): ViewHolder {
        val view = LayoutInflater.from(context).inflate(R.layout.tvshow, parent, false)
        return ViewHolder(view)
    }

    override fun onBindViewHolder(holder: ViewHolder, position: Int) {
        val article = articles[position]
        holder.bind(article)
    }

    override fun getItemCount() = articles.size
    inner class ViewHolder(itemView: View) : RecyclerView.ViewHolder(itemView),
        View.OnClickListener {

        private val mediaImageView = itemView.findViewById<ImageView>(R.id.mediaImage)
        private val mediaTitleView = itemView.findViewById<TextView>(R.id.mediaTitle)

        init {
            itemView.setOnClickListener(this)
        }

        override fun onClick(v: View?) {
            // Get selected article
            val article = articles[absoluteAdapterPosition]

            //  Navigate to Details screen and pass selected article
            val intent = Intent(context, DetailActivity::class.java)
            intent.putExtra(TVSHOW_EXTRA, article)
            context.startActivity(intent)
        }
        fun bind(flixster: TVShow) {
            mediaTitleView.text = flixster.name

            Glide.with(context)
                .load("https://image.tmdb.org/t/p/w500" + flixster.poster_path)
                .into(mediaImageView)
        }
    }
}