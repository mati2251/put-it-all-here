struct book {
    int id;
    char title[100];
    char author[100];
    int year;
};

#define NUMBER_OF_BOOKS 30

struct book books[NUMBER_OF_BOOKS + 1] = {
        {0,  "The Lord of the Rings",                     "J.R.R. Tolkien", 1954},
        {1,  "The Hobbit",                                "J.R.R. Tolkien", 1937},
        {2,  "The Silmarillion",                          "J.R.R. Tolkien", 1977},
        {3,  "The Hitchhiker's Guide to the Galaxy",      "Douglas Adams",  1979},
        {4,  "The Restaurant at the End of the Universe", "Douglas Adams",  1980},
        {5,  "Life, the Universe and Everything",         "Douglas Adams",  1982},
        {6,  "So Long, and Thanks for All the Fish",      "Douglas Adams",  1984},
        {7,  "Mostly Harmless",                           "Douglas Adams",  1992},
        {8,  "The Hitchhiker's Guide to the Galaxy",      "Douglas Adams",  2005},
        {9,  "The Hitchhiker's Guide to the Galaxy",      "Douglas Adams",  2009},
        {10, "The Republic",                              "Plato",          380},
        {11, "The Phaedo",                                "Plato",          360},
        {12, "The Phaedrus",                              "Plato",          360},
        {13, "The Symposium",                             "Plato",          360},
        {14, "The Apology",                               "Plato",          360},
        {15, "The Crito",                                 "Plato",          360},
        {16, "The Meno",                                  "Plato",          360},
        {17, "The Gorgias",                               "Plato",          360},
        {18, "The Euthyphro",                             "Plato",          360},
        {19, "The Euthydemus",                            "Plato",          360},
        {20, "The Laches",                                "Plato",          360},
        {21, "The Charmides",                             "Plato",          360},
        {22, "The Lysis",                                 "Plato",          360},
        {23, "The Hippias Major",                         "Plato",          360},
        {24, "The Hippias Minor",                         "Plato",          360},
        {25, "The Ion",                                   "Plato",          360},
        {26, "The Menexenus",                             "Plato",          360},
        {27, "The Statesman",                             "Plato",          360},
        {28, "The Laws",                                  "Plato",          360},
        {29, "The Symposium",                             "Plato",          360},
        {30, "The Republic",                              "Plato",          360}
};