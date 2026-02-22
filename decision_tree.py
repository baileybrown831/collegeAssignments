import numpy as np

def create_decision_tree(dataset, attributes, label):
    #min_data = np.array(int)
    decision_tree = []
    #print(dataset)
    df = dataset[:,-1]
    datum = np.unique(df[label], return_counts = True)
    print(datum[1])
    unique_data = np.unique(dataset[label])
    #print(len(unique_data))
    
    if len(unique_data) <= 1:
        return unique_data[0]
    
    elif len(attributes) == 0:
        return unique_data[np.argmax(datum[1])]

    elif len(dataset) == 0:
        return label
    
    else:
        label = int(unique_data[np.argmax(datum[1])])
        
        
        item_values = [calculate_information_gain(dataset, attribute, label) for attribute in attributes]
        #print(item_values)
        optimum_feature = attributes[np.argmax(item_values)]
        #print(optimum_feature)
        for value in np.unique(dataset[:,optimum_feature]):
            #print(dataset[:,optimum_feature])
            #print(np.unique(dataset[:,optimum_feature]))
            
            rows = np.where(dataset[:,optimum_feature] == value)
            #print(rows[0])
            #print(dataset[rows[0]])
            min_data = dataset[rows[0]]
            if(len(rows) > 1):
                iterrows = iter(rows)
                next(iterrows)
                for row in iterrows:
                    np.vstack((min_data, dataset[row]))
                
            attributes.remove(optimum_feature)
            min_tree = create_decision_tree(min_data, attributes, label)
            
            decision_tree[optimum_feature][value] = min_tree
            
    return decision_tree


def calculate_information_gain(dataset, feature, label):
    #print(feature)
    #print(dataset)
    dataset_entropy = calculate_entropy(dataset[label])
    values, feat_counts = np.unique(dataset[feature], return_counts = True)
    
    weighted_feature_entropy = np.sum([(feat_counts[i]/np.sum(feat_counts))*calculate_entropy(np.where(dataset[feature]
                                == values[i])[label]) for i in range(len(values))])
    feature_info_gain = dataset_entropy - weighted_feature_entropy
    return feature_info_gain


def calculate_entropy(df_label):
    classes, class_counts = np.unique(df_label, return_counts = True)
    entropy_value = np.sum([(-class_counts[i]/np.sum(class_counts))*np.log2(class_counts[i]/np.sum(class_counts))
                        for i in range(len(classes))])
    
    return entropy_value






############main##############
trainingFile = "pendigits_training.txt"
testFile = "pendigits_test.txt"
    
train = np.loadtxt(trainingFile)
test = np.loadtxt(testFile)

features = [0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15]
label = 0

create_decision_tree(train, features, label)




