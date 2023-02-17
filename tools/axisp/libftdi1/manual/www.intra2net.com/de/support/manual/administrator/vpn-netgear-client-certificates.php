<!DOCTYPE html>
    <html><head>
      <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
   <title>Zertifikate | Administrator Handbuch
  </title>
      <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <link rel="stylesheet" type="text/css" media="screen" href="../../../screen.css">
    <link rel="stylesheet" type="text/css" media="print" href="../../../print.css">
    <meta name="generator" content="DocBook XSL Stylesheets V1.74.3"><link rel="home" href="index.php" title="Intra2net Administrator Handbuch"><link rel="up" href="vpn-netgear-client.php" title="43. Kapitel - VPN mit dem NetGear ProSafe Client"><link rel="prev" href="vpn-netgear-client-installation.php" title="43.2. Installation"><link rel="next" href="vpn-netgear-client-connections.php" title="43.4. Verbindungen">
    <meta http-equiv="content-language" content="de">
  </head><body>
          
    <!-- header start -->

<div id="header">

<div id="logo">
	<a href="../../../index.html">
		<div id="logo_screen"><img src="../../../pictures/intra2net.gif" alt="Intra2net AG"></div>
		<div id="logo_print"><img src="../../../pictures/intra2net_print.gif" alt="Intra2net AG"></div>
	</a>
</div>

<div id="search">
	<form name="formsearch" method="get" action="http://www.intra2net.com/search/search.cgi">
		<input type="text" name="q" maxlength="64" id="searchinput" value="">
		<input type="image" name="submit" src="../../../pictures/search.gif" alt="Suche">
	</form>
</div>


<nav id="navigation">

<a href="vpn-netgear-client-certificates.php#navigation"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>
<a href="vpn-netgear-client-certificates.php#"><div class="mobilemenu"><img src="../../../pictures/mobile_icon.gif" alt="Navigation"></div></a>

<ul class="navbar">

<li id="Produkte"><a href="../../../../en/products/index.html">Produkte</a>
	<div class="dropdown">
		<div class="navgrid">
			<div class="navgrid-unit navcol1_of_3">
				<h4>SOFTWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/index.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/intranator.php">Business Server</a></li>
						<li><a href="../../../produkte/security_gateway.php">Security Gateway</a></li>
						<li><a href="../../../produkte/network_security.php">Network Security</a></li>
						<li><a href="../../../produkte/lizenzen/index.php">Lizenzbestimmungen</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>HARDWARE</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/hardware.php">&Uuml;bersicht</a></li>
						<li><a href="../../../produkte/appliance_eco.php">Appliance Eco</a></li>
						<li><a href="../../../produkte/appliance_pro.php">Appliance Pro</a></li>
						<li><a href="../../../produkte/appliance_ultimate.php">Appliance Ultimate</a></li>
					</ul>
			</div>
			<div class="navgrid-unit navcol1_of_3">
				<h4>REFERENZEN</h4>
					<ul class="navmenu">
						<li><a href="../../../produkte/anwenderberichte.php">Anwenderberichte</a></li>
						<li><a href="../../../produkte/kundenstimmen.php">Kundenstimmen</a></li>
						<li><a href="../../../produkte/pressestimmen.php">Pressestimmen</a></li>
					</ul>
			</div>
		</div> <!-- close .grid div -->
	</div> <!-- close .dropdown div -->
</li>

<li id="Download"><a href="../../../download.1">Download</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../download/index.php">Software</a></li>
			<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
			<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
		</ul>
	</div>
</li>

<li id="Support" class="selected"><a href="../../../../en/support/index.html">Support</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../anfrage.php">Support-Anfrage</a></li>
			<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
			<li><a href="http://forum.intra2net.com/">Forum</a></li>
			<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
			<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
			<li><a href="../../schulung.php">Schulung</a></li>
			<li><a href="../../fernwartung.php">Fernwartung</a></li>
		</ul>
	</div>
</li>

<li id="Kaufen"><a href="../../../kaufen/index.html">Kaufen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../kaufen/index.php">Partner finden</a></li>
			<li><a href="../../../partner-werden">Partner werden</a></li>
			<li><a href="http://partner.intra2net.com/">Partnerweb</a></li>
		</ul>
	</div>
</li>

<li id="Unternehmen"><a href="../../../unternehmen/index.html">Unternehmen</a>
	<div class="dropdown">
		<ul>
			<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
			<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
			<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
			<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
		</ul>
	</div>
</li>

</ul> <!-- close #navbar ul -->

</nav>

</div> <!-- close #header div -->


<div id="page">


<div id="content">

<!-- header end -->

    <div id="manual">
    <!-- content start -->

    <div class="navheader"><table width="100%" summary="Navigation header"><tr><th colspan="3" align="center">43.3. Zertifikate</th></tr><tr><td width="20%" align="left"><a accesskey="p" href="vpn-netgear-client-installation.php">Zur&uuml;ck</a>&nbsp;</td><th width="60%" align="center">43. Kapitel - VPN mit dem NetGear ProSafe Client</th><td width="20%" align="right">&nbsp;<a accesskey="n" href="vpn-netgear-client-connections.php">Weiter</a></td></tr></table><hr></div><div class="sect1" lang="de"><div class="titlepage"><div><div><h2 class="title" style="clear: both"><a name="vpn-netgear-client-certificates"></a>43.3. Zertifikate</h2></div></div></div><p>
      </p><div class="orderedlist"><ol type="1"><li><p>Netgear ProSafe kann keine eigenen Zertifikate erstellen. Dies &uuml;bernimmt daher das
            Programm <span class="command"><strong>makecert</strong></span>. Starten Sie die
            <span class="command"><strong>makecert</strong></span>-Batchdatei und w&auml;hlen eine Laufzeit in Jahren f&uuml;r Ihr
            Zertifikat.</p><pre class="programlisting">C:\makecert&gt;makecert
Gueltigkeit des neuen Zertifikats:
1. Ein Jahr
2. Zwei Jahre
3. Drei Jahre
4. Vier Jahre
5. Fuenf Jahre
Ihre Wahl: 5

C:\makecert&gt;openssl req -x509 -newkey rsa:2048 -days 1825 -new -nodes -config 
openssl.cnf -outform PEM -keyform PEM -keyout privatekey.pem -out newcert.cer
Using configuration from openssl.cnf
Loading 'screen' into random state - done
Generating a 2048 bit RSA private key
........................+++
...............................................................+++
writing new private key to 'privatekey.pem'
-----
You are about to be asked to enter information that will be incorporated
into your certificate request.
What you are about to enter is what is called a Distinguished Name or a DN.
There are quite a few fields but you can leave some blank
For some fields there will be a default value,
If you enter '.', the field will be left blank.</pre></li><li><p>Geben Sie jetzt die Daten des Rechners ein. F&uuml;r einige Felder gibt es einen
            Standardwert der in eckigen Klammern angegeben ist. Wollen Sie diesen verwenden, so
            dr&uuml;cken Sie einfach nur Return. Verwenden Sie keine Umlaute und andere Sonderzeichen, da
            es sonst zu Problemen kommen kann. Der &#8220;Common Name&#8221; (oder &#8220;Rechnername&#8221; auf dem
            Intranator) muss eindeutig sein und darf nicht auf anderen Rechnern oder f&uuml;r eine CA
            wiederverwendet werden.</p><pre class="programlisting">Country Name (2 letter code) []:
State or Province Name (full name) []:
Locality Name (eg, city) []:
Organization Name (eg, company) []:Intra2net AG
Organizational Unit Name (eg, section) []:
Common Name (eg, your name or your server's hostname) []:Netgear Client
Email Address []:

C:\makecert&gt;openssl pkcs12 -export -in newcert.cer -inkey privatekey.pem 
-out newcert.p12
Loading 'screen' into random state - done</pre></li><li><p>W&auml;hlen Sie ein Transportpasswort, mit dem die Schl&uuml;sseldatei auf dem Weg zum
            VPN-Client gesch&uuml;tzt wird. Netgear ProSafe akzeptiert keine leeren Passw&ouml;rter.</p><pre class="programlisting">Enter Export Password:
Verifying password - Enter Export Password:

C:\makecert&gt;del privatekey.pem</pre></li><li><p>Starten Sie den Netgear Certificate Manager aus dem Kontextmen&uuml; (Rechtsklick) des
            SafeNet Symbols in der Traybar</p></li><li><p>W&auml;hlen Sie den Reiter &#8220;My Certificates&#8221; und klicken Sie auf &#8220;Import
            Certificate&#8221;.</p><div class="mediaobject"><img src="../images/vpn/netgear-client/01-mycert.png"></div></li><li><p>Aktivieren Sie &#8220;Import certificate to local machine store&#8221;, w&auml;hlen das
            Zertifikatspaket newcert.p12 aus dem makecert-Verzeichnis aus und geben Sie das von
            Ihnen gew&auml;hlte Transportpasswort ein.</p><div class="mediaobject"><img src="../images/vpn/netgear-client/02-import.png"></div></li><li><p>&Uuml;berpr&uuml;fen Sie, ob das Zertifikat vertrauensw&uuml;rdig ist. W&auml;hlen das eben installiere
            Zertifikat aus und klicken auf &#8220;Verify&#8221;. Das Zertifikat muss als &#8220;is valid&#8221; eingestuft
            sein.</p><div class="mediaobject"><img src="../images/vpn/netgear-client/05-validcheck.png"></div></li><li><p><a name="vpn-netgear-client-certificates-trust"></a>Wechseln Sie auf den Reiter &#8220;Trust Policy&#8221; und schalten auf &#8220;Trust specific root
            CAs&#8221;</p><div class="mediaobject"><img src="../images/vpn/netgear-client/06-trust.png"></div></li><li><p>Gehen Sie auf dem Intranator in das Men&uuml; &#8220;System &gt; Schl&uuml;ssel &gt; Eigene
            Schl&uuml;ssel&#8221;. W&auml;hlen Sie einen Schl&uuml;ssel f&uuml;r diese Verbindung aus oder erstellen Sie einen
            neuen. Wechseln Sie auf den Reiter &#8220;Daten&#8221;, gehen Sie auf &#8220;Zertifikat exportieren&#8221; und
            speichern das Zertifikat.</p></li><li><p>Gehen Sie im Netgear Certificate Manager auf den Reiter &#8220;Root CA Certificates&#8221; und
            klicken auf &#8220;Import Certificate&#8221;. W&auml;hlen Sie als Dateityp &#8220;All files&#8221; und importieren
            das eben aus dem Intranator gespeicherte Zertifikat.</p><div class="mediaobject"><img src="../images/vpn/netgear-client/07-intra-imp.png"></div></li><li><p>Gehen Sie im Intranator in das Men&uuml; <span class="guimenu">System&nbsp;&gt;&nbsp;Schl&uuml;ssel&nbsp;&gt;&nbsp;Fremde
	  Schl&uuml;ssel</span> und klicken auf <span class="guimenuitem">Neu</span>. Tragen Sie einen beliebigen
            Namen ein und &ouml;ffnen Sie die newcert.cer-Datei aus dem makecert-Verzeichnis in einem
            beliebigen Editor (z.B. wordpad). Kopieren Sie den Inhalt in die Zwischenablage und f&uuml;gen
            Sie sie in das Schl&uuml;sselfeld auf dem Intranator ein.</p></li></ol></div><p>
    </p></div><div class="navfooter"><hr><table width="100%" summary="Navigation footer"><tr><td width="40%" align="left"><a accesskey="p" href="vpn-netgear-client-installation.php">Zur&uuml;ck</a>&nbsp;</td><td width="20%" align="center"><a accesskey="u" href="vpn-netgear-client.php">Nach oben</a></td><td width="40%" align="right">&nbsp;<a accesskey="n" href="vpn-netgear-client-connections.php">Weiter</a></td></tr><tr><td width="40%" align="left" valign="top">43.2. Installation&nbsp;</td><td width="20%" align="center"><a accesskey="h" href="index.php">Zum Anfang</a></td><td width="40%" align="right" valign="top">&nbsp;43.4. Verbindungen</td></tr></table></div>
      
    <!-- content end -->
    </div>

  <!-- footer start -->

</div> <!-- close content <div> -->
</div> <!-- close page <div> -->

<div id="sitemap">

<div id="sitemapcol1">
	<a href="../../../produkte/index.php" class="sitemapheader">Produkte</a>
	<ul class="sitemap">
	<li><a href="../../../produkte/intranator.php">Intra2net Business Server</a></li>
	<li><a href="../../../produkte/security_gateway.php">Intra2net Security Gateway</a></li>
	<li><a href="../../../produkte/network_security.php">Intra2net Network Security</a></li>
	<li><a href="../../../produkte/appliance_eco.php">Intra2net Appliance Eco</a></li>
	<li><a href="../../../produkte/appliance_pro.php">Intra2net Appliance Pro</a></li>
	<li><a href="../../../produkte/appliance_ultimate.php">Intra2net Appliance Ultimate</a></li>
	</ul>
</div>

<div id="sitemapcol2">
	<a href="../../../download/index.php" class="sitemapheader">Download</a>
	<ul class="sitemap">
	<li><a href="../../../download/index.php">Software</a></li>
	<li><a href="../../../download/datenblaetter.php">Datenbl&auml;tter</a></li>
	<li><a href="../../../download/handbuecher.php">Handb&uuml;cher</a></li>
	</ul>
</div>

<div id="sitemapcol3">
	<a href="../../index.php" class="sitemapheader">Support</a>
	<ul class="sitemap">
	<li><a href="../../anfrage.php">Support-Anfrage</a></li>
	<li><a href="../../handbuecher.php">Handb&uuml;cher</a></li>
	<li><a href="http://forum.intra2net.com/">Forum</a></li>
	<li><a href="../../unterstuetzte_hardware.php">Unterst&uuml;tzte Hardware</a></li>
	<li><a href="../../antispam/index.html">Blacklist Performance</a></li>
	<li><a href="../../schulung.php">Schulung</a></li>
	<li><a href="../../fernwartung.php">Fernwartung</a></li>
	</ul>
</div>

<div id="sitemapcol4">
	<a href="../../../kaufen/index.php" class="sitemapheader">Kaufen</a>
	<ul class="sitemap">
	<li><a href="../../../kaufen/index.php">Partner finden</a></li>
	<li><a href="../../../partner-werden">Partner werden</a></li>
	<li><a href="https://partner.intra2net.com/">Partnerweb</a></li>
	</ul>
</div>

<div id="sitemapcol5">
	<a href="../../../unternehmen/index.php" class="sitemapheader">Unternehmen</a>
	<ul class="sitemap">
	<li><a href="../../../unternehmen/index.php">&Uuml;ber Intra2net</a></li>
	<li><a href="../../../unternehmen/presse/index.php">Presse</a></li>
	<li><a href="../../../unternehmen/karriere.php">Karriere</a></li>
	<li><a href="../../../unternehmen/kontakt.php">Kontakt</a></li>
	</ul>
</div>

</div> <!-- close sitemap <div> -->


<div id="footnote">
	<div id="footnotecompany">

		&copy; Intra2net AG 2015
	</div>

	<div id="footnotelinks">
		<a href="../../../impressum.php">Impressum</a>
		<a href="../../../../en/developer/index.html">Entwickler</a>
		<a href="../../../datenschutz.php">Datenschutz</a>
		<a href="../../../unternehmen/kontakt.php">Kontakt</a>
	</div>
</div>

<script type="text/javascript">

  var _gaq = _gaq || [];
  _gaq.push(['_setAccount', 'UA-151599-1']);
  _gaq.push(['_gat._anonymizeIp'])
  _gaq.push(['_trackPageview']);

  (function() {
    var ga = document.createElement('script'); ga.type = 'text/javascript'; ga.async = true;
    ga.src = ('https:' == document.location.protocol ? 'https://ssl' : 'http://www') + '.google-analytics.com/ga.js';
    var s = document.getElementsByTagName('script')[0]; s.parentNode.insertBefore(ga, s);
  })();

</script>

<!-- PHP error counter: 0 -->

<!-- footer end -->

    </body></html>