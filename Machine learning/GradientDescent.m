% o:n 
% x:nXm
hyp=o*x
err=hyp-y
gradient=0.01*(x*err')
o=o-gradient'

