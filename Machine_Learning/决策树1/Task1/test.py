import read_data
import pandas as pd

data=pd.read_csv("lenses.txt",sep='\t',header=None)

dict=read_data.value_count(data.iloc[:,4])
dict