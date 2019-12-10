package com.company;

public class surgeon implements doctor {
    private int operations_performed = 0;

    public surgeon(int operations_performed) {
        this.operations_performed = operations_performed;
    }
}
