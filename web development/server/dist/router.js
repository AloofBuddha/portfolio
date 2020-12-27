"use strict";
var __importStar = (this && this.__importStar) || function (mod) {
    if (mod && mod.__esModule) return mod;
    var result = {};
    if (mod != null) for (var k in mod) if (Object.hasOwnProperty.call(mod, k)) result[k] = mod[k];
    result["default"] = mod;
    return result;
};
Object.defineProperty(exports, "__esModule", { value: true });
const express_1 = require("express");
const db = __importStar(require("./db.json"));
const router = express_1.Router();
router.get('/classroom', (req, res) => {
    res.send({
        id: db.classRoom.id,
        name: db.classRoom.name,
    });
});
router.get('/teacher', (req, res) => {
    const { firstName, lastName } = db.classRoom.teacher;
    res.send({
        id: db.classRoom.teacher.id,
        name: `${firstName} ${lastName}`,
    });
});
router.get('/students', (req, res) => {
    const students = db.classRoom.students.map((student) => {
        return {
            id: student.id,
            name: `${student.firstName} ${student.lastName}`,
            grade: Number.parseInt(student.grade, 10),
        };
    });
    res.send({ students });
});
router.get('/average', (req, res) => {
    const grades = db.classRoom.students.map((student) => {
        return Number.parseInt(student.grade, 10);
    });
    const average = grades.reduce((acc, x) => acc + x, 0) / grades.length;
    res.send({
        classRoomId: db.classRoom.id,
        average,
    });
});
exports.default = router;
//# sourceMappingURL=router.js.map