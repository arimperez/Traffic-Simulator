typedef struct patientInfo{
    char *id;
    char *symptom;
    int priority;
} Patient;

Patient *initializePatient(char *id, char *symptom, int priority);
