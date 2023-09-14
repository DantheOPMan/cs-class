
package com.example.wordlegame

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.EditText
import android.widget.TextView
import android.widget.Toast
import com.example.wordlegame.FourLetterWordList

class MainActivity : AppCompatActivity() {
    var wordToGuess = ""
    var count = 0
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        val four = FourLetterWordList()
        val button = findViewById<Button>(R.id.submitButton)
        val input = findViewById<EditText>(R.id.inputText)
        val display1 = findViewById<TextView>(R.id.Guess1)
        val checkGuess1 = findViewById<TextView>(R.id.Guess1Check)
        val display2 = findViewById<TextView>(R.id.Guess2)
        val checkGuess2 = findViewById<TextView>(R.id.Guess2Check)
        val display3 = findViewById<TextView>(R.id.Guess3)
        val checkGuess3 = findViewById<TextView>(R.id.Guess3Check)
        var solutionText = findViewById<TextView>(R.id.solutionText)

        wordToGuess = four.getRandomFourLetterWord()
        button.setOnClickListener {
            if (count == 3){
                count = 0
                wordToGuess = four.getRandomFourLetterWord().uppercase()
                display1.text = ""
                checkGuess1.text = ""
                display2.text = ""
                checkGuess2.text = ""
                display3.text = ""
                checkGuess3.text = ""
                button.text= "Submit"
                solutionText.text = ""
            }
            var inputText = input.text.toString().uppercase()
            input.text = null
            if(inputText.length == 4){
                count++
                var outputText = checkGuess(inputText)

                if (count == 1){
                    display1.text = inputText
                    checkGuess1.text = outputText
                }else if (count == 2){
                    display2.text = inputText
                    checkGuess2.text = outputText
                }else if (count == 3){
                    display3.text = inputText
                    checkGuess3.text = outputText
                    button.text = "Restart"
                }
                if(outputText == "OOOO"){
                    count ==3
                    button.text = "Restart"
                    Toast.makeText(this, "Congrats You're right!", Toast.LENGTH_SHORT).show()
                    solutionText.text = wordToGuess

                }else if(count == 3){
                    solutionText.text = wordToGuess
                }
            }else{
                if(inputText.isNotEmpty()){
                    Toast.makeText(this, "Word Must be 4 Letters", Toast.LENGTH_SHORT).show()
                }
            }

        }

    }
    fun checkGuess(guess: String) : String {
        var result = ""
        for (i in 0..3) {
            if (guess[i] == wordToGuess[i]) {
                result += "O"
            }
            else if (guess[i] in wordToGuess) {
                result += "+"
            }
            else {
                result += "X"
            }
        }
        return result
    }
}