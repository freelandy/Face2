using System;
using System.Drawing;
using System.Diagnostics;
using System.Collections.Generic;
using System.IO;
using Face = Face2;
using Microsoft.VisualStudio.TestTools.UnitTesting;


namespace UnitTestProject1
{
    [TestClass]
    public class UnitTest1
    {
        [TestMethod]
        public void TestMethod1()
        {
            Bitmap bmp1 = (Bitmap)Bitmap.FromFile("1.png");
            Face.Aligner aligner = new Face.Aligner("models\\PointDetector2.0.pts5.ats");
            Face.Detector detector = new Face.Detector("models\\Detector2.0.ats");
            Face.Recognizer recognizer = new Face.Recognizer("models\\Recognizer2.0.ats");

            Stopwatch sw = new Stopwatch();
            sw.Start();

            List<Rectangle> faces1 = detector.Detect(bmp1);
            List<Rectangle> faces2 = detector.Detect(bmp1);
            sw.Stop();

            long detect = sw.ElapsedMilliseconds;

            sw.Restart();
            List<PointF> pt1 = aligner.Align(bmp1, faces1[0]);
            List<PointF> pt2 = aligner.Align(bmp1, faces2[1]);
            sw.Stop();

            long align = sw.ElapsedMilliseconds;

            sw.Restart();
            double s = recognizer.Verify(bmp1, pt1, bmp1, pt2);
            sw.Stop();

            long recognize = sw.ElapsedMilliseconds;

            for (int i = 0; i < faces1.Count; i++)
            {
                Console.WriteLine(faces1[i].X + "\t" + faces1[i].Y + "\t" + faces1[i].Width + "\t" + faces1[i].Height);
            }

            Console.WriteLine(s);
            Console.WriteLine("detect:" + detect);
            Console.WriteLine("align:" + align);
            Console.WriteLine("recognize:" + recognize);
        }


        [TestMethod]
        public void TestMethod2()
        {
            Bitmap bmp1 = (Bitmap)Bitmap.FromFile("1.png");
            Face.Aligner aligner = new Face.Aligner("models\\PointDetector2.0.pts5.ats");
            Face.Detector detector = new Face.Detector("models\\Detector2.0.ats");
            Face.Recognizer recognizer = new Face.Recognizer("models\\Recognizer2.0.ats");

            Stopwatch sw = new Stopwatch();
            sw.Start();

            List<Rectangle> faces1 = detector.Detect(bmp1);
            List<Rectangle> faces2 = detector.Detect(bmp1);
            sw.Stop();

            long detect = sw.ElapsedMilliseconds;

            sw.Restart();
            List<PointF> pt1 = aligner.Align(bmp1, faces1[0]);
            List<PointF> pt2 = aligner.Align(bmp1, faces2[1]);
            sw.Stop();

            long align = sw.ElapsedMilliseconds;

            sw.Restart();
            long idx1 = recognizer.Register(bmp1, pt1);
            long idx2 = recognizer.Register(bmp1, pt2);
            sw.Stop();
            long register = sw.ElapsedMilliseconds;

            sw.Restart();
            float similarity = 0;
            long idx = recognizer.Identify(bmp1, pt2, ref similarity);
            sw.Stop();
            long identify = sw.ElapsedMilliseconds;

            sw.Restart();
            double s = recognizer.Verify(bmp1, pt1, bmp1, pt2);
            sw.Stop();

            long verify = sw.ElapsedMilliseconds;

            for (int i = 0; i < faces1.Count; i++)
            {
                Console.WriteLine(faces1[i].X + "\t" + faces1[i].Y + "\t" + faces1[i].Width + "\t" + faces1[i].Height);
            }

            Console.WriteLine(s);
            Console.WriteLine("detect:" + detect);
            Console.WriteLine("align:" + align);
            Console.WriteLine("verify:" + verify);
            Console.WriteLine("register:" + register);
            Console.WriteLine("identify:" + identify);
            Console.WriteLine("idx1:" + idx1);
            Console.WriteLine("idx2:" + idx2);
            Console.WriteLine("identified idx:" + idx);
        }


        [TestMethod]
        public void TestMethod3()
        {
            Face.Aligner aligner = new Face.Aligner("models\\PointDetector2.0.pts5.ats");
            Face.Detector detector = new Face.Detector("models\\Detector2.0.ats");
            Face.Recognizer recognizer = new Face.Recognizer("models\\Recognizer2.0.ats");

            Stopwatch sw = new Stopwatch();
            int error_cnt = 0;
            int no_face_error = 0;
            string base_path = "E:\\Downloads\\test_photo";
            for (int i = 1; i <= 716; i++)
            {
                sw.Restart();

                string file_name_1 = string.Format("{0}\\{1:D4}\\01.jpg", base_path, i);
                string file_name_2 = string.Format("{0}\\{1:D4}\\02.jpg", base_path, i);
                string file_name_3 = string.Format("{0}\\{1:D4}\\03.jpg", base_path, i);

                if (!new FileInfo(file_name_1).Exists)
                {
                    continue;
                }
                if (!new FileInfo(file_name_2).Exists)
                {
                    continue;
                }
                if (!new FileInfo(file_name_3).Exists)
                {
                    continue;
                }

                Bitmap bmp1 = (Bitmap)Bitmap.FromFile(file_name_1);
                Bitmap bmp2 = (Bitmap)Bitmap.FromFile(file_name_2);
                Bitmap bmp3 = (Bitmap)Bitmap.FromFile(file_name_3);

                List<Rectangle> faces1 = detector.Detect(bmp1);
                List<Rectangle> faces2 = detector.Detect(bmp2);
                List<Rectangle> faces3 = detector.Detect(bmp3);

                if (faces1.Count < 1)
                {
                    no_face_error++;
                    continue;
                }
                if (faces2.Count < 1)
                {
                    no_face_error++;
                    continue;
                }
                if (faces3.Count < 1)
                {
                    no_face_error++;
                    continue;
                }


                List<PointF> pts1 = aligner.Align(bmp1, faces1[0]);
                List<PointF> pts2 = aligner.Align(bmp2, faces2[0]);
                List<PointF> pts3 = aligner.Align(bmp3, faces3[0]);

                double s1 = recognizer.Verify(bmp1, pts1, bmp2, pts2);
                double s2 = recognizer.Verify(bmp1, pts1, bmp3, pts3);
                double s3 = recognizer.Verify(bmp2, pts2, bmp3, pts3);

                sw.Stop();

                if (s1 < 0.7)
                {
                    error_cnt++;
                }
                if (s2 < 0.7)
                {
                    error_cnt++;
                }
                if (s3 < 0.7)
                {
                    error_cnt++;
                }

                Console.WriteLine("person:" + i + "\t time:" + sw.ElapsedMilliseconds);
            }

            Console.WriteLine("total error:" + error_cnt);
            Console.WriteLine("no_face error:" + no_face_error);
        }
    }
}
