package com.example.flixster2

import android.os.Bundle
import android.widget.ImageView
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity
import com.bumptech.glide.Glide

private const val TAG = "DetailActivity"

class DetailActivity : AppCompatActivity() {
    private lateinit var mediaImageView: ImageView
    private lateinit var titleTextView: TextView
    private lateinit var dateTextView: TextView
    private lateinit var overviewTextView: TextView
    private lateinit var languageTextView: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.tvshows_detail)

        mediaImageView = findViewById(R.id.mediaImage)
        titleTextView = findViewById(R.id.mediaTitle)
        dateTextView = findViewById(R.id.mediaDate)
        overviewTextView = findViewById(R.id.mediaOverview)
        languageTextView = findViewById(R.id.mediaLanguage)

        val person = intent.getSerializableExtra(TVSHOW_EXTRA) as TVShow

        titleTextView.text = person.name
        dateTextView.text = person.first_air_date
        overviewTextView.text = person.overview
        languageTextView.text = person.original_language
        Glide.with(this)
            .load("https://image.tmdb.org/t/p/w500" + person.backdrop_path)
            .into(mediaImageView)
    }
}