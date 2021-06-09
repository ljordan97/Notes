import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt
#import a csv, convert to Data Frame
user_data = pd.read_csv("file.csv")
pop_data = pd.read_csv("pop_data.csv")

#display 1st 15 lines of Dframe
print(user_data.head(15))

#match "city name" entry in two Dframes
# and merge all corresponding data ...lots of documentation here
new_df = pd.merge(user_data, pop_data)

#show new Dframe
print(new_df.head(15))

#pull info from a Dframe as list, target column by name after '.'
new_df.loc[new_df.population_proper < 100000, "location"] = "rural"

#create a list from a column of a Dframe
age = new_df["age"]
#create distribution plot (histogram) using seaborn
sns.displot(age)