package wc;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class Wordcount {
	
	public static void main(String[] args) throws Exception
	{
		Configuration c = new Configuration();
		String[] file = new GenericOptionsParser(c,args).getRemainingArgs();
		Path input = new Path(file[0]);
		Path output = new Path(file[1]);
		
		Job j = new Job();
		j.setJarByClass(Wordcount.class);
		j.setMapperClass(MapForwc.class);
		j.setReducerClass(ReduceForwc.class);
		j.setOutputKeyClass(Text.class);
		j.setOutputValueClass(IntWritable.class);
		
		FileInputFormat.addInputPath(j, input);
		FileOutputFormat.setOutputPath(j, output);
		System.exit(j.waitForCompletion(true)?0:1);
		
	}

}
