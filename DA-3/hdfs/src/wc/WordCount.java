package wc;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class WordCount {
	
	public static void main(String[] args) throws Exception
	{
		Configuration config = new Configuration();
		String[] file = new GenericOptionsParser(config,args).getRemainingArgs();
		Path input = new Path(file[0]);
		Path ouput = new Path(file[1]);
		
		Job j = new Job();
		j.setJarByClass(WordCount.class);
		j.setMapperClass(MapForwc.class);
		j.setReducerClass(ReduceForwc.class);
		j.setOutputKeyClass(Text.class);
		j.setOutputValueClass(IntWritable.class);
		
		FileInputFormat.addInputPath(j,input);
		FileOutputFormat.setOutputPath(j, ouput);
		System.exit(j.waitForCompletion(true)?0:1);				
	}

}

class MapForwc extends Mapper<LongWritable, Text, Text, IntWritable>{
	public void map(LongWritable key, Text value, Context con) throws IOException, InterruptedException
	{
		String line = value.toString();
		String[] words = line.split(",");
		
		Text outputKey = null;
		IntWritable outputValue;
		
		for(String word : words){
			outputKey = new Text(word.toUpperCase().trim());
			outputValue = new IntWritable(1);
			con.write(outputKey,outputValue);
		}
	}
}

class ReduceForwc extends Reducer<Text, IntWritable, Text, IntWritable>{
	public void reduce(Text item, Iterable<IntWritable> value, Context con) throws IOException, InterruptedException{
		int sum=0;
		for(IntWritable val : value){
			sum=sum+val.get();
		}
		con.write(item, new IntWritable(sum));
	}
}