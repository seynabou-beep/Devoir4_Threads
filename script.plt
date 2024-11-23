# Configuration pour affichage à l'écran
set terminal qt persist

# Style du graphique
set title 'Evolution des valeurs entre les threads'
set xlabel 'Iterations'
set ylabel 'Valeurs'
set grid

# Affichage du graphe
plot 'resultat.txt' using 0:1 with lines title 'Compteur' linewidth 2

# Pause pour garder la fenêtre ouverte
pause -1
