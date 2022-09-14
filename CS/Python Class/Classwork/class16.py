class State:

    def __init__(self, name):
        self.name = name
        self.universities = []
    
    def add_university(self, university):
        self.universities.append(university)

    def is_home_of(self, university):
        if(university in self.universities):
            return True
        return False

class Section:
    def __init__(self, section_id):
        self.section_id = section_id
        self.enrolled_students = []
    def enroll(self, studentName):
        self.enrolled_students.append(studentName)
    def is_enrolled(self, studentName):
        if(studentName in self.enrolled_students):
            return True
        return False


class CollegeDirectory:
    def __init__(self, name):
        self.name = name
        self.students = {}
    def addStudent(self, student, email):
        self.students[student] = email
    def getEmailList(self):
        output = ""
        for student in self.students.keys():
            output += student + "<" + self.students[student] + "> "
        return output
    