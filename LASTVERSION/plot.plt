set term png
set output 'graficos/BUCKET_vIntAleatorio.png'
set encoding utf8

set xlabel "n (tamanho do vetor)"
set ylabel "Tempo (ns)"
set xtics nomirror
set ytics nomirror

set key Left 
set key left top

t(x) = a*x**2 + b*x + c
fit t(x) 'resultados/BUCKET_Aleatorio.txt' using 1:2 via a, b, c

titulo = sprintf("T(n) = %.4gn**2 + %.4gn + %.4g",a,b,c)
titulo = sprintf("Método do bucket sort com vetor em ordem aleatória\n%s", titulo)
set title titulo

plot 'resultados/BUCKET_Aleatorio.txt' title "medições" with points, \
     t(x) title "T(n)" lt 1 lc 3
