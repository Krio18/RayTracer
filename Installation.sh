#!/bin/bash

REPO_URL="git@github.com:Krio18/RayTracer.git"
INSTALL_DIR="RayTracer"

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

error_exit() {
    echo -e "${RED}[ERREUR] $1${NC}" 1>&2
    exit 1
}

success() {
    echo -e "${GREEN}[SUCCÈS] $1${NC}"
}

install_prerequisites() {
    local packages=("git" "g++" "make" "libconfig++-dev")

    for pkg in "${packages[@]}"; do
        if ! dpkg -s $pkg > /dev/null 2>&1; then
            echo "Installation de $pkg..."
            sudo apt-get install -y $pkg || error_exit "Impossible d'installer $pkg."
        else
            success "$pkg est déjà installé."
        fi
    done
}

clone_repo() {
    if [ -d "$INSTALL_DIR" ]; then
        echo "Le répertoire $INSTALL_DIR existe déjà. Suppression en cours..."
        rm -rf $INSTALL_DIR || error_exit "Impossible de supprimer le répertoire $INSTALL_DIR."
    fi

    git clone $REPO_URL $INSTALL_DIR || error_exit "Impossible de cloner le dépôt."
    success "Dépôt cloné avec succès dans $INSTALL_DIR."
}

build_project() {
    cd $INSTALL_DIR || error_exit "Impossible d'accéder au répertoire $INSTALL_DIR."
    make || error_exit "La construction du projet a échoué."
    success "Projet construit avec succès."
}

main() {
    install_prerequisites
    clone_repo
    build_project
    success "Installation et configuration terminées avec succès."
}

main
