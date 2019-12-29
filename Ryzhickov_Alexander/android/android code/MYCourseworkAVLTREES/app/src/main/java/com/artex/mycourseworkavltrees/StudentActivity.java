package com.artex.mycourseworkavltrees;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.animation.ObjectAnimator;
import android.os.Bundle;
import android.view.View;
import android.view.animation.Animation;
import android.view.animation.AnimationUtils;
import android.widget.Button;
import android.widget.EditText;
import android.widget.RadioButton;
import android.widget.TextView;
import android.widget.Toast;

import com.google.android.gms.tasks.OnCompleteListener;
import com.google.android.gms.tasks.Task;
import com.google.firebase.firestore.CollectionReference;
import com.google.firebase.firestore.DocumentReference;
import com.google.firebase.firestore.FirebaseFirestore;
import com.google.firebase.firestore.WriteBatch;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Locale;

public class StudentActivity extends AppCompatActivity {

    EditText editText;
    RadioButton buttonSimple;
    RadioButton buttonMedium;
    RadioButton buttonHigh;
    Button button;
    TextView textView3;

    TextView options;
    TextView deleteElements;
    TextView answer_text;
    EditText answer_text2;
    TextView reponse;
    Button send;

    String answer;
    String attempt = "0";

    Animation main_animation;
    boolean isTrueAnswer = false;
    int count_attempt = 3;

    String dateText;
    String timeText;

    private FirebaseFirestore db = FirebaseFirestore.getInstance();
    private CollectionReference notebookRef = db.collection("Notebook");

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_student);

        main_animation = AnimationUtils.loadAnimation(this, R.anim.atg3);

        editText = findViewById(R.id.editText);
        textView3 = findViewById(R.id.textView3);
        options = findViewById(R.id.option);
        deleteElements = findViewById(R.id.delete_elements);

        options = findViewById(R.id.option);
        deleteElements = findViewById(R.id.delete_elements);
        answer_text = findViewById(R.id.answer1);
        answer_text2 = findViewById(R.id.anwer2);
        reponse = findViewById(R.id.textView_reponse);
        send = findViewById(R.id.button2);

        options.setVisibility(View.INVISIBLE);
        deleteElements.setVisibility(View.INVISIBLE);
        answer_text.setVisibility(View.INVISIBLE);
        answer_text2.setVisibility(View.INVISIBLE);
        reponse.setVisibility(View.INVISIBLE);
        send.setVisibility(View.INVISIBLE);

        buttonSimple = findViewById(R.id.radioButton);
        buttonMedium = findViewById(R.id.radioButton2);
        buttonHigh = findViewById(R.id.radioButton3);
        buttonMedium.setChecked(true);

        buttonSimple.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                buttonSimple.setChecked(true);
                buttonMedium.setChecked(false);
                buttonHigh.setChecked(false);
            }
        });

        buttonMedium.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                buttonSimple.setChecked(false);
                buttonMedium.setChecked(true);
                buttonHigh.setChecked(false);
            }
        });

        buttonHigh.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                buttonSimple.setChecked(false);
                buttonMedium.setChecked(false);
                buttonHigh.setChecked(true);
            }
        });

        button = findViewById(R.id.button);
        button.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (!editText.getText().toString().trim().equals("")) {
                    saveNote();
                } else {
                    Toast.makeText(getApplicationContext(), "Поле вашего имени пусто", Toast.LENGTH_SHORT).show();
                }
            }
        });

        send.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                if (!isTrueAnswer) {
                    if (!attempt.equals("3")) {
                        if (attempt.equals("0")) {
                            attempt = "1";
                            count_attempt--;
                        } else {
                            if (attempt.equals("1")) {
                                attempt = "2";
                                count_attempt--;
                            } else {
                                if (attempt.equals("2")) {
                                    attempt = "3";
                                    answer_text2.setEnabled(false);
                                    count_attempt--;
                                }
                            }
                        }
                        //Toast.makeText(getApplicationContext(), attempt, Toast.LENGTH_LONG).show();
                        WriteBatch batch = db.batch();
                        DocumentReference sfRef = db.collection("Notebook").document(editText.getText().toString() + " " + dateText + " " + timeText);
                        batch.update(sfRef, "attempt", attempt);
                        if (answer.equals(answer_text2.getText().toString())) {
                            batch.update(sfRef, "done", "yes");
                            answer_text2.setEnabled(false);
                            isTrueAnswer = true;
                            reponse.setText("Answer is correct");
                            reponse.setTextColor(getResources().getColor(R.color.green));
                        } else {
                            batch.update(sfRef, "done", "no");
                            reponse.setText("Answer isn't correct, you have " + Integer.toString(count_attempt) + " attempts");
                            reponse.setTextColor(getResources().getColor(R.color.red));
                        }
                        batch.commit().addOnCompleteListener(new OnCompleteListener<Void>() {
                            @Override
                            public void onComplete(@NonNull Task<Void> task) {
                                Toast.makeText(getApplicationContext(), "Ответ отправлен успешно", Toast.LENGTH_LONG).show();
                            }
                        });
                    }
                    if (attempt.equals("3")) {
                        Toast.makeText(getApplicationContext(), "Вы израсходавали все попытки", Toast.LENGTH_LONG).show();
                    }
                }
            }
        });

    }

    private void saveNote() {
        String name = editText.getText().toString();

        String complexity = "medium";
        if (buttonSimple.isChecked()) {
            complexity = "simple";
        }

        if (buttonMedium.isChecked()) {
            complexity = "medium";
        }

        if (buttonHigh.isChecked()) {
            complexity = "High";
        }

        String string = "";
        int count = 0;
        int countDeleteElements = 0;

        if (buttonSimple.isChecked()) {
            string = createSimpleVariant();
            count = 5;
            countDeleteElements = 1;
        }
        if (buttonMedium.isChecked()) {
            string = createMediumVariant();
            count = 10;
            countDeleteElements = 2;
        }
        if (buttonHigh.isChecked()) {
            string = createHighVariant();
            count = 15;
            countDeleteElements = 3;
        }


        String[] Array = string.split(";");
        options.append(Array[0]);
        deleteElements.append(Array[1]);
        answer = Array[2];
        //Toast.makeText(getApplicationContext(), answer, Toast.LENGTH_LONG).show();

        //CollectionReference notebookRef = FirebaseFirestore.getInstance().collection("Notebook");
        //notebookRef.add(new Student(name, complexity, "no", Array[0], Array[1], Array[2],attempt));
        Date currentDate = new Date();
        DateFormat dateFormat = new SimpleDateFormat("dd.MM.yyyy", Locale.getDefault());
        dateText = dateFormat.format(currentDate);
// Форматирование времени как "часы:минуты:секунды"
        DateFormat timeFormat = new SimpleDateFormat("HH:mm:ss", Locale.getDefault());
        timeText = timeFormat.format(currentDate);
        db.collection("Notebook").document(name + " " + dateText + " " + timeText).set(new Student(name, complexity, "no yet", Array[0], Array[1], Array[2], attempt));

        editText.setEnabled(false);
        ObjectAnimator animation = ObjectAnimator.ofFloat(button, "translationX", -100f);
        animation.setDuration(200);
        animation.start();

        ObjectAnimator anim = ObjectAnimator.ofFloat(button, "alpha", 0f);
        anim.setDuration(200); // duration 3 seconds
        anim.start();

        ObjectAnimator animation2 = ObjectAnimator.ofFloat(textView3, "translationX", -100f);
        animation2.setDuration(200);
        animation2.start();

        ObjectAnimator anim2 = ObjectAnimator.ofFloat(textView3, "alpha", 0f);
        anim2.setDuration(200); // duration 3 seconds
        anim2.start();

        options.setVisibility(View.VISIBLE);
        deleteElements.setVisibility(View.VISIBLE);
        answer_text.setVisibility(View.VISIBLE);
        answer_text2.setVisibility(View.VISIBLE);
        reponse.setVisibility(View.VISIBLE);
        send.setVisibility(View.VISIBLE);

        options.startAnimation(main_animation);
        deleteElements.startAnimation(main_animation);
        answer_text.startAnimation(main_animation);
        answer_text2.startAnimation(main_animation);
        reponse.startAnimation(main_animation);
        send.startAnimation(main_animation);

        button.setClickable(false);
        textView3.setVisibility(View.INVISIBLE);
        buttonSimple.setClickable(false);
        buttonMedium.setClickable(false);
        buttonHigh.setClickable(false);
    }

    public native String createSimpleVariant();

    public native String createMediumVariant();

    public native String createHighVariant();

}
