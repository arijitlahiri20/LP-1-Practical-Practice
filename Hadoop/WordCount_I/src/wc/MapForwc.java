package wc;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class MapForwc extends Mapper<LongWritable, Text, Text, IntWritable>{
	
	public void map(LongWritable key, Text value, Context con) throws IOException, InterruptedException
	{
		String line = value.toString();
		String[] words = line.split(",");
		
		Text outputKey = null;
		IntWritable outputValue;
		
		for(String word : words)
		{
			outputKey = new Text(word.toUpperCase().trim());
			outputValue = new IntWritable(1);
			con.write(outputKey, outputValue);
		}
	}

}
