The is a small example of how to create heiracrhtical clusters.  To make this 
work there is a type erasure class clusterable which will wrap any object 
which has a charge function and is copy constructable. To see how it works 
look at clusterable example.  

The charge functionality depends on ADL and may be fragile.  
