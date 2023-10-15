package com.codepath.articlesearch

import androidx.room.ColumnInfo
import androidx.room.Entity
import androidx.room.PrimaryKey

@Entity(tableName = "nutrition_table")
class NutritionEntity (
    @PrimaryKey(autoGenerate = true) val id: Long = 0,
    @ColumnInfo(name = "nutritionName") val nutritionName: String?,
    @ColumnInfo(name = "calorieCount") val calorieCount: String?
)