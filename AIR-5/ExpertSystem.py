import sys

fileName = sys.argv[1]
symptomDictionary = {}
symptomToDiseaseMap = {}
diseaseMatch = {}

def read(dataFileName=fileName):
    dataFile = open(dataFileName, 'r')

    for line in dataFile:
        tokens = line.split(',')
        symptomsList = []
        diseaseName = tokens[0][1:-1]

        symptomCount = len(tokens)

        for index in range(1, symptomCount):
            symptom = tokens[index].strip()
            symptomsList.append(symptom)

            if symptom not in symptomToDiseaseMap.keys():
                symptomToDiseaseMap[symptom] = list()

            symptomToDiseaseMap[symptom].append(diseaseName)

        symptomDictionary[diseaseName] = symptomsList

def detectDisease():
    symptoms = input('Enter the symptoms(comma seperated): : ')
    symptomList = symptoms.split(',')

    inputSize = len(symptomList)

    for index in range(0, inputSize):
        symptomList[index] = symptomList[index].strip().lower()

    print('The given symptoms are: : ', symptomList)

    totalCount = 0.0

    for disease in symptomDictionary.keys():
        count = 0.0
        symptoms = symptomDictionary[disease]
        for symptom in symptomList:
            if symptom in symptoms:
                count += 1

        if count > 0:
            totalCount += count
            diseaseMatch[disease] = count

    for key, value in sorted(diseaseMatch.items(), key = lambda keyValue:keyValue[1], reverse=True):
        print('The possibility of having %s is %.2f %%' % (key, (value * 100)/totalCount))



def calculateProbability(diseaseName, diseaseSymptoms, symptomList):
    symptomsCount = len(diseaseSymptoms)
    count = 0.0

    for symptom in symptomList:
        if symptom in diseaseSymptoms:
            count += 1

    
    #print('Probability of having {} is {}'.format(diseaseName, str(count/symptomsCount)))

read(fileName)
detectDisease()
