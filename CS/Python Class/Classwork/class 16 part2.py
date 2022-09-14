import class16

myState = class16.State("New Jersey")
myState.add_university("NJIT")
myState.add_university("RUTGERS")
print(myState.is_home_of("NJIT"))
print(myState.is_home_of("MIT"))

myClass = class16.Section("H15")
myClass.enroll("Daniel Yankovich")
myClass.enroll("Charles Wang")
print(myClass.is_enrolled("George Hanna"))
print(myClass.is_enrolled("Daniel Yankovich"))

myCollege = class16.CollegeDirectory("NJIT")
myCollege.addStudent("Daniel Yankovich", "soccerdan34@gmail.com")
myCollege.addStudent("Lilia Bose", "liliabose@gmail.com")
print(myCollege.getEmailList())