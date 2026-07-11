### Building Efficient Data Structures for Large Medical Records and Data Querying

The purpose of this project is to facilitate the retrieval of hospitals' patients' information. This project supports the storage, querying, and data retrieval of patient data.

### Features

- Splay Tree and Skip List data structures to store and subsequently retrieve patient data.
- Can read given CSV files containing every patient's data.
- Interactive menu with options to query by age or age range.

### Setup & Execution

#### Initial Setup

1. Begin by building the executable.
2. Run the program, the following menu TUI will be displayed:

```text
==================================================
         HEALTHCARE DATABASE SYSTEM MENU
==================================================
1. Load Patient Dataset
2. Exact Patient Lookup (by Patient Age)
3. Demographic Range Query (by Age)
4. Exit
   ==================================================
   Enter your choice (1-4):
````

#### Execution
1. Select option **1** to load the patient dataset you wish inquire about.
2. Enter the dataset relative file path.

3. The search engines are ready!
    - Option **2** will ask for the specific patient age; enter a positive number
      - ```Enter the dataset file path: [age]```
    - Option **3** will ask for an age range; enter two positive numbers
        - ```
          Enter minimum age: [lower age]
          Enter maximum age: [higher age]
          ```
4. Once done, simply enter option **4** to exit.

### Collaborators

**Andres Godoy, Sai Rajan, Joshua Chalar** 