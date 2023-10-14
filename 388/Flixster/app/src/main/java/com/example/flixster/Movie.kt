package com.example.flixster

import com.google.gson.annotations.SerializedName

class Movie {

    @SerializedName("original_title")
    var title: String? = null

    @SerializedName("overview")
    var overview: String? = null


    @SerializedName("poster_path")
    var posterPath: String? = null

}