package com.artex.mycourseworkavltrees;

import androidx.appcompat.app.AppCompatActivity;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'native-lib' library on application startup.
    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

       /* // Example of a call to a native method
        TextView tv = findViewById(R.id.sample_text);
        int a = stringFromJNI2();
        Toast.makeText(this,Integer.toString(a),Toast.LENGTH_LONG).show();

        TextView tv2 = findViewById(R.id.textView);
        TextView tv3 = findViewById(R.id.textView2);

        tv.setText(stringFromJNI3(1));
        tv2.setText(stringFromJNI3(2));

        int aaa[] = {1,2,3,4,5};

        tv3.setText(Integer.toString(addArray(aaa)));*/

        findViewById(R.id.constraint1).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(),TeacherActivity.class);
                startActivity(intent);
            }
        });

        findViewById(R.id.constraint2).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                Intent intent = new Intent(getApplicationContext(),StudentActivity.class);
                startActivity(intent);
            }
        });

    }

    /**
     * A native method that is implemented by the 'native-lib' native library,
     * which is packaged with this application.
     */
    public native String stringFromJNI();
    public native int stringFromJNI2();
    public native String stringFromJNI3(int complexity);


    public static native int addArray(int []arr);


}
