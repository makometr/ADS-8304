package com.artex.mycourseworkavltrees;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ImageView;
import android.widget.TextView;

import androidx.annotation.NonNull;
import androidx.recyclerview.widget.RecyclerView;

import com.firebase.ui.firestore.FirestoreRecyclerAdapter;
import com.firebase.ui.firestore.FirestoreRecyclerOptions;

import java.util.List;

public class Adapter extends FirestoreRecyclerAdapter<Student, Adapter.ViewHolder> {

    public Adapter(@NonNull FirestoreRecyclerOptions<Student> options) {
        super(options);
    }

    @Override
    protected void onBindViewHolder(@NonNull ViewHolder holder, int position, @NonNull Student model) {
        holder.name.setText(model.getName());
        holder.complexity.setText(model.getComplexity());
        if(model.getDone().equals("yes")) {
            holder.imageView.setColorFilter(holder.itemView.getContext().getResources().getColor(R.color.green));
        }
        if(model.getDone().equals("no")) {
            holder.imageView.setColorFilter(holder.itemView.getContext().getResources().getColor(R.color.red));
        }

        holder.insert.setText("Insert: "+model.getOption());
        holder.delete.setText("Delete: " +model.getDeleteElements());
        holder.answer.setText("Answer"+model.getAnswer());
        holder.attempt.setText("Attempt: "+model.getAttempt());
    }

    public void deleteItem(int position){
        getSnapshots().getSnapshot(position).getReference().delete();
    }

    @NonNull
    @Override
    public ViewHolder onCreateViewHolder(@NonNull ViewGroup parent, int viewType) {
        View view = LayoutInflater.from(parent.getContext()).inflate(R.layout.student_layout, parent, false);
        return new ViewHolder(view);
    }

    public class ViewHolder extends RecyclerView.ViewHolder {

        private ImageView imageView;
        private TextView name;
        private TextView complexity;

        private TextView insert;
        private TextView answer;
        private TextView attempt;
        private TextView delete;

        public ViewHolder(@NonNull View itemView) {
            super(itemView);

            imageView = itemView.findViewById(R.id.isDone);
            name = itemView.findViewById(R.id.name);
            complexity = itemView.findViewById(R.id.complexity);

            insert = itemView.findViewById(R.id.insert);
            delete = itemView.findViewById(R.id.delete);
            attempt = itemView.findViewById(R.id.attempt);
            answer = itemView.findViewById(R.id.answer);
        }
    }
}

