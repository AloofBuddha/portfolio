import { Router } from 'express';

import * as db from './db.json';

const router = Router();

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

export default router;
