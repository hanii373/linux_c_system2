#define NB_ARGUMENTS_MAX 10

int decouperCommande(char *commande, char *arguments[]) {
    int nbArguments = 0;
    int i = 0;
    while (commande[i] != '\0') {
        if (commande[i] == ' ') {
            commande[i] = '\0';
        } else if (
            (i == 0 || commande[i - 1] == '\0') &&
            commande[i] != '\0' &&
            nbArguments < NB_ARGUMENTS_MAX
        ) {
            arguments[nbArguments] = &commande[i];
            nbArguments++;
        }
        i++;
    }
    arguments[nbArguments] = NULL;
    return nbArguments;
}

