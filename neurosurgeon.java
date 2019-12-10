package com.company;

public class neurosurgeon extends surgeon {
    private String research_method;

    public neurosurgeon(int operations_performed, String research_method) {
        super(operations_performed);
        this.research_method = research_method;
    }
}
