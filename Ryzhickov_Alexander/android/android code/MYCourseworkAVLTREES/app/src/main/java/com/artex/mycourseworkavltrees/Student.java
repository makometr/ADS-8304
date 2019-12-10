package com.artex.mycourseworkavltrees;

public class Student {

    String name;
    String complexity;
    String done;
    String option;
    String deleteElements;
    String answer;
    String attempt;

    public Student() {

    }

    public Student(String name, String complexity, String done, String option, String deleteElements, String answer, String attempt) {
        this.name = name;
        this.complexity = complexity;
        this.done = done;
        this.option = option;
        this.deleteElements = deleteElements;
        this.answer = answer;
        this.attempt = attempt;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getComplexity() {
        return complexity;
    }

    public void setComplexity(String complexity) {
        this.complexity = complexity;
    }

    public String getDone() {
        return done;
    }

    public void setDone(String done) {
        this.done = done;
    }

    public String getOption() {
        return option;
    }

    public void setOption(String option) {
        this.option = option;
    }

    public String getDeleteElements() {
        return deleteElements;
    }

    public void setDeleteElements(String deleteElements) {
        this.deleteElements = deleteElements;
    }

    public String getAnswer() {
        return answer;
    }

    public void setAnswer(String answer) {
        this.answer = answer;
    }

    public String getAttempt() {
        return attempt;
    }

    public void setAttempt(String attempt) {
        this.attempt = attempt;
    }
}
